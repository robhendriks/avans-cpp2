#include "game.hpp"
#include "server.hpp"
#include "string_utils.hpp"
#include "colors.hpp"
#include "game_state_lobby.hpp"
#include "list_dialog.hpp"
#include "card_deck_dialog.hpp"
#include "random_utils.hpp"
#include "command_builder.hpp"
#include "character_card_factory.hpp"
#include "koning.hpp"

namespace machiavelli
{
    void game::init()
    {
        try {
            m_vars.save_default(VARS_FILE_NAME);
            m_vars.load(VARS_FILE_NAME);
        } catch (const std::exception& e) {
            log(WARN) << e.what();
        }
        
        try {
            m_card_manager.load();
        } catch (const std::exception& e) {
            log(ERROR) << "Error: " << e.what();
        }
        
        register_command()
            .name("help")
            .description("displays the help dialog")
            .callback([](command_sender& sender, const command_args& args) {
                auto& ch = command_handler::get_instance();
                
                if (args.size() < 1) {
                    sender.show(ch.get_help_dialog());
                } else {
                    auto& cmd = ch.find(args[0]);
                    sender.show(cmd.to_string());
                }
                return true;
            });
        
        register_command()
            .name("about")
            .description("display about message")
            .callback([](command_sender& sender, const command_args& args) {
                sender.message("\e[1mMachiavelli v1.0");
                sender.message("\e[2m(c) Rob Hendriks & Niels Snakenborg");
                return true;
            });
        
        register_command()
            .name("info")
            .description("displays server information")
            .callback([this](command_sender& sender, const command_args& args) {
                sender.message(m_server.to_string());
                return true;
            });
        
        register_command()
            .name("whois")
            .description("display player information")
            .usage("<name>")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) { return false; }
                
                auto client = get_client_by_player_name(args[0]);
                sender.message(client->to_string());
                
                return true;
            });
        
        register_command()
            .name("whoami")
            .description("display your information")
            .callback([this](command_sender& sender, const command_args& args) {
                sender.message(sender.to_string());
                return true;
            });
        
        register_command()
            .name("list")
            .description("list players")
            .callback([this](command_sender& sender, const command_args& args) {
                this->for_each_client([&sender](auto& client) {
                    sender.message(client.to_string());
                });
                return true;
            });
        
        register_command()
            .name("set")
            .description("set server variable")
            .usage("<key> <value>")
            .visible(false)
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 2) {
                    return false;
                }
                m_vars.set(args[0], std::stoi(args[1]));
                warn("Player '" + sender.get_player().get_display_name() + "' changed var '" + args[0] + "' to " + args[1], true);
                return true;
            });
        
        register_command()
            .name("get")
            .description("print a single or all server variables")
            .usage("[key]")
            .visible(false)
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) {
                    sender.message(m_vars.to_string());
                    return true;
                }
                sender.message(std::to_string(m_vars.get(args[0])));
                return true;
            });
        
        register_command()
            .name("quit_server")
            .description("stop the server")
            .callback([this](command_sender& sender, const command_args& args) {
                m_server.stop();
                return true;
            });
        
        register_command()
            .name("quit")
            .description("leave the game")
            .callback([](command_sender& sender, const command_args& args) {
                sender.quit();
                return true;
            });
        
        register_command()
            .name("stop")
            .description("stop the game")
            .callback([this](command_sender& sender, const command_args& args) {
                m_state_manager.next<game_state_lobby>();
                return true;
            });
        
        register_command()
            .name("clear")
            .description("clear display")
            .callback([](command_sender& sender, const command_args& args) {
                sender.clear();
                return true;
            });
        
        register_command()
            .name("chat")
            .description("send a message")
            .usage("<message>")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) { return false; }
                const std::string msg = string_utils::join(args, ' ');
                broadcast("<\e[38;5;108m" + sender.get_player().get_display_name() + "\e[0m> " + msg);
                return true;
            });
        
        register_command()
            .name("nick")
            .description("change your in-game name")
            .usage("<new_name>")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) { return false; }
                
                auto old_name = sender.get_player().get_name();
                auto new_name = args[0];
                
                if (!string_utils::is_snake_case(args[0])) {
                    throw std::invalid_argument{"Invalid name \'" + new_name + '\''};
                } else if (!player_name_available(new_name)) {
                    throw std::invalid_argument{"Name \'" + new_name + "' cannot be used twice"};
                }
                
                sender.get_player().set_name(new_name);
                warn("Player '" + old_name + "' has been renamed '" + new_name + '\'', true);
                return true;
            });
        
        register_command()
            .name("deck")
            .description("display your cards")
            .usage("<characters|buildings>")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) { return false; }

                if (levenshtein_match("characters", args[0])) {
                    sender.show(sender.get_player().get_characters());
                } else if (levenshtein_match("buildings", args[0])) {
                    sender.show(sender.get_player().get_buildings());
                } else {
                    return false;
                }
                return true;
            });
        
        register_command()
            .name("built")
            .description("display built buildings")
            .usage("[player]")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) {
                    card_deck_dialog<building_card> d{sender.get_player().get_built_buildings()};
                    sender.show(d);
                } else {
                    auto client = get_client_by_player_name(args[0]);
                    card_deck_dialog<building_card> d{client->get_player().get_built_buildings()};
                    sender.show(d);
                }
                return true;
            });
        
        register_command()
            .name("global_deck")
            .description("display global cards")
            .usage("<characters|buildings>")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) { return false; }
                
                if (levenshtein_match("characters", args[0])) {
                    sender.show(get_characters());
                } else if (levenshtein_match("buildings", args[0])) {
                    sender.show(get_buildings());
                } else {
                    return false;
                }
                return true;
            });
        
        register_command()
            .name("stats")
            .description("display statistics")
            .callback([](command_sender& sender, const command_args& args) {
                sender.message(sender.get_player().get_stats().to_string());
                return true;
            });
        
        register_command()
            .name("gold")
            .description("display gold")
            .callback([](command_sender& sender, const command_args& args) {
                int balance = sender.get_player().get_wallet().get_balance();
                sender.message("\e[38;5;136m" + std::to_string(balance) + " gold");
                return true;
            });
        
        return_to_lobby();
    }
    
    void game::deinit()
    {
        try {
            m_vars.save(VARS_FILE_NAME);
        } catch (const std::exception& e) {
            log(ERROR) << "Error: " << e.what();
        }
    }
    
    void game::return_to_lobby()
    {
        m_state_manager.next<game_state_lobby>();
    }
    
    void game::reset()
    {
        m_last_round = false;
        
        // Reset characters deck
        m_characters = card_deck<character_card>{m_card_manager.get_characters()};
        m_characters.shuffle(3);
        
        // Reset buildings deck
        m_buildings = card_deck<building_card>{m_card_manager.get_buildings()};
        m_buildings.shuffle(3);
        
        // Reset clients
        reset_clients();
    }
    
    void game::reset_clients()
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        for (auto client : m_clients) {
            client->get_player().reset();
        }
        lock.unlock();
    }
    
    void game::set_new_king(std::shared_ptr<client_info> new_king)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        
        std::for_each(m_clients.begin(), m_clients.end(), [new_king](auto client) {
            client->get_player().set_new_king(client == new_king);
        });
    }
    
    std::shared_ptr<client_info> game::find_new_king()
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        
        auto it = std::find_if(m_clients.begin(), m_clients.end(), [](auto client) {
            return client->get_player().is_new_king();
        });
        
        std::for_each(m_clients.begin(), m_clients.end(), [](auto client) {
            if (client->get_player().is_king()) { client->get_player().set_king(false); }
        });
        
        if (it == m_clients.end()) {
            return nullptr;
        }
        log(DBG) << "Found new king: " << (*it)->get_player().get_name();
        return *it;
    }
    
    std::shared_ptr<client_info> game::pick_new_king()
    {
        if (auto new_king = find_new_king()) {
            return new_king;
        }
        
        log(DBG) << "Chosing random king";
        
        std::lock_guard<std::mutex> lock{m_mutex};
        randomizer r{0, static_cast<int>(m_clients.size() - 1)};
        
        auto it = m_clients.begin();
        std::advance(it, r.random());
        
        if (it == m_clients.end()) {
            return nullptr;
        }
        
        auto client = *it;
        client->get_player().set_new_king(true);
        return client;
    }
    
    void game::pick_king()
    {
        if (auto king = pick_new_king()) {
            auto& p = king->get_player();
            p.set_king(true);
            
            warn("Player " + p.get_name() + " has been crowned king");
        }
    }
    
    void game::remove_top_character()
    {
        // Notify the king that the top card has been remove
        auto c = get_characters().pop();
        if (auto king = get_king()) {
            king->warn("Card '" + c->get_name() + "' was on top of the deck and has been removed", true);
            set_current_player(king);
        }
    }
    
    void game::reset_characters()
    {
        // Reset characters deck
        reset_player_characters();
        
        m_characters = card_deck<character_card>{m_card_manager.get_characters()};
        m_characters.shuffle(3);
        
        for (auto c : m_characters) {
            c->reset();
        }
        
        remove_top_character();
    }
    
    void game::reset_player_characters()
    {
        for_each_client([this](client_info& client) {
            client.get_player().get_characters().clear();
        });
    }
    
    void game::join(std::shared_ptr<client_info> client)
    {
        if (!client) { return; }
        
        std::unique_lock<std::mutex> g{m_mutex};
        m_clients.insert(client);
        g.unlock();
        
        client->message("\e[2J\e[0;0H" + m_server.get_motd());
        warn(client->get_player().get_name() + " joined the game");
        m_state_manager.on_client_enter(*client);
    }
    
    void game::leave(std::shared_ptr<client_info> client)
    {
        if (!client) { return; }
        
        warn(client->get_player().get_name() + " left the game");
        m_state_manager.on_client_leave(*client);
        
        std::lock_guard<std::mutex> g{m_mutex};
        m_clients.erase(client);
    }
    
    void game::on_command(const client_command& cmd)
    {
        auto client = cmd.get_client().lock();
        if (!client) { return; }
        
        m_state_manager.on_client_command(*client, cmd.get_text());
    }
    
    void game::send(std::shared_ptr<client_info> client, const std::string& msg)
    {
        if (client && !client->is_silent()) {
            client->message(msg);
        }
    }
    
    void game::broadcast(const std::string& msg)
    {
        std::lock_guard<std::mutex>{m_mutex};
        
        log(INFO) << "[BROADCAST] " << string_utils::strip_ansi(msg);
        
        for (auto client : m_clients) {
            if (!client || client->is_silent()) { continue; }
            client->message(msg);
        }
    }
    
    void game::info(const std::string& msg, bool dim)
    {
        broadcast(colorize_info(msg, dim));
    }
    
    void game::warn(const std::string& msg, bool dim)
    {
        broadcast(colorize_warning(msg, dim));
    }
    
    void game::error(const std::string& msg, bool dim)
    {
        broadcast(colorize_error(msg, dim));
    }
    
    void game::for_each_client(std::function<void(client_info&)> callback)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        for (auto client : m_clients) {
            callback(*client);
        }
    }
    
    size_t game::get_client_count()
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        return m_clients.size();
    }
    
    std::shared_ptr<client_info> game::get_king()
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        
        for (auto client : m_clients) {
            if (client->get_player().is_king()) {
                return client;
            }
        }
        return nullptr;
    }
    
    void game::set_current_player(std::shared_ptr<client_info> current_player)
    {
        if (m_current_player) {
            m_current_player->on_turn_end();
        }
        m_current_player = current_player;
        if (m_current_player) {
            m_current_player->on_turn_begin();
        }
    }
    
    std::shared_ptr<client_info> game::peek_player()
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        
        auto it = std::find_if(m_clients.begin(), m_clients.end(), [this](auto client) {
            return client != m_current_player;
        });
        
        if (it == m_clients.end()) {
            throw std::runtime_error{"Unexpected error"};
        }
        
        return *it;
    }
    
    void game::advance_player()
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        
        auto it = std::find_if(m_clients.begin(), m_clients.end(), [this](auto client) {
            return client != m_current_player;
        });
        
        if (it == m_clients.end()) {
            throw std::runtime_error{"Unexpected error"};
        }
        
        set_current_player(*it);
    }
    
    std::shared_ptr<client_info> game::get_client_by_player_name(const std::string& name)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        auto it = std::find_if(m_clients.begin(), m_clients.end(), [&name](auto client) {
            return string_utils::to_lower_case_copy(client->get_player().get_name()) == string_utils::to_lower_case_copy(name);
        });
        if (it == m_clients.end()) {
            throw std::invalid_argument{"unknown player '" + name + '\''};
        }
        return *it;
    }
    
    std::shared_ptr<character_card> game::get_character_by_name(const std::string& name)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        
        auto it = std::find_if(m_clients.begin(), m_clients.end(), [name](std::shared_ptr<client_info> client) {
            return client->get_player().get_characters().find(name) != nullptr;
        });
        if (it == m_clients.end()) {
            throw std::runtime_error{"Character '" + name + "' not found"};
        }
        return (*it)->get_player().get_characters().find(name);
    }
    
    bool game::player_name_available(const std::string& name)
    {
        try {
            get_client_by_player_name(name);
            return false;
        } catch (...) {
            return true;
        }
    }
    
    std::tuple<player*, int> game::get_player_with_most_buildings()
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        
        std::vector<std::tuple<player*, int>> results;
        for (auto client : m_clients) {
            results.emplace_back(&client->get_player(), client->get_player().get_built_buildings().size());
        }
        
        std::sort(results.begin(), results.end(), [](auto a, auto b) {
            return std::get<1>(a) > std::get<1>(b);
        });
        
        return results.front();
    }
    
    std::vector<stats> game::get_stats()
    {
        std::vector<stats> result;
        std::transform(m_clients.begin(), m_clients.end(), std::back_inserter(result), [](auto client) {
            return client->get_player().get_stats();
        });
        return result;
    }
}
