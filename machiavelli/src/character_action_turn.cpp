#include "character_action_turn.hpp"
#include "turn_manager.hpp"
#include "game.hpp"
#include "game_state_play.hpp"
#include "game_state_end.hpp"
#include "command_builder.hpp"
#include "character_pick_turn.hpp"

namespace machiavelli
{
    void character_action_turn::register_commands()
    {
        register_command()
            .name("done")
            .description("end your current turn")
            .callback([this](command_sender& sender, const command_args& args) {
                if (sender.get_player().is_turn_over()) { throw std::runtime_error{"It's not your turn"}; }
                
                get_context().next<character_action_turn>();
                
                return true;
            });
        
        register_command()
            .name("pick")
            .usage("<gold|building>")
            .description("get 2 pieces of gold or pick a building card")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) { return false; }
                else if (sender.get_player().is_turn_over()) { throw std::runtime_error{"It's not your turn"}; }
                
                auto& g = get_context().get_game();
                auto& p = sender.get_player();
                
                if (p.has_picked()) {
                    throw std::runtime_error{"You've already picked gold or a building this round"};
                }
                
                if (args[0] == "gold") {
                    p.get_wallet().add(2);
                    p.set_picked(true);
                    sender.info("Added 2 gold coins to your wallet");
                } else if (args[0] == "building") {
                    auto& bo = p.get_build_options();
                    
                    if (args.size() < 2) {
                        if (bo.empty()) {
                            bo.push(g.get_buildings().pop());
                            bo.push(g.get_buildings().pop());
                        }
                        sender.show(p.get_build_options());
                    } else {
                        auto card = bo.pop_at(std::stoi(args[1]));
                        p.get_buildings().push(card);
                        bo.transfer_back(g.get_buildings());
                        
                        sender.info("Added '" + card->get_name() + "' to your buildings deck");
                        p.set_picked(true);
                    }
                } else {
                    return false;
                }
                
                return true;
            });
        
        register_command()
            .name("build")
            .usage("<card_index>")
            .description("build a card from the buildings deck")
            .callback([this](command_sender& sender, const command_args& args) {
                if (args.size() < 1) { return false; }
                else if (sender.get_player().is_turn_over()) { throw std::runtime_error{"It's not your turn"}; }
                
                auto& g = get_context().get_game();
                auto& p = sender.get_player();
                
                auto& gs = get_context().get_state();
                auto& ci = gs.get_character_iterator();
                
                int build_count = p.get_build_count();
                int max_build_count = ci.get_current_character()->max_build_count();
                
                if (g.get_vars().is_false("sv_ignore_build_limits") && build_count >= max_build_count) {
                    throw std::runtime_error{"You've built " + std::to_string(build_count) + " out of " + std::to_string(max_build_count) + " building(s)"};
                }
                
                size_t i = std::stoi(args[0]);
                auto card = p.get_buildings().peek_at(i);
                p.get_wallet().remove(card->get_cost());
                p.get_buildings().pop_at(i);
                
                p.get_built_buildings().push(card);
                p.set_build_count(p.get_build_count() + 1);
                
                g.info("A '" + card->get_name() + "\' has been built by '" + p.get_display_name() + '\'');
                return true;
            });
        
        register_command()
            .name("use")
            .usage("[args...]")
            .description("use character special")
            .callback([this](command_sender& sender, const command_args& args) {
                if (sender.get_player().is_turn_over()) { throw std::runtime_error{"It's not your turn"}; }
                
                auto& g = get_context().get_game();
                auto& gs = get_context().get_state();
                auto& ci = gs.get_character_iterator();
                
                auto character = ci.get_current_character();
                character->use(g, sender, args);
                
                return true;
            });
    }
    
    void character_action_turn::on_enter()
    {
        turn::on_enter();
        
        auto& g = get_context().get_game();
        auto& gs = get_context().get_state();
        auto& ci = gs.get_character_iterator();
    
        if (!ci.advance()) {
            log(INFO) << "Character iterator has reached the end";
            
            if (g.is_last_round()) {
                log(WARN) << "Game has ended";
                get_context().get_state().get_context().next<game_state_end>();
                return;
            }
            
            get_context().reset_round();
            get_context().next<character_pick_turn>();
            return;
        }
        
        log(INFO) << "Calling character '" + ci.get_current_character()->get_name() + '\'';
        
        auto client = ci.get_current_player();
        if (client == nullptr || !ci.get_current_character()->is_alive()) {
            log(INFO) << "Skipping character '" + ci.get_current_character()->get_name() + '\'';
            
            get_context().next<character_action_turn>();
            return;
        } else {
            get_context().reset_turn();
            get_context().get_game().set_current_player(client);
            
            client->set_silent(true);
            g.warn("It's the " + ci.get_current_character()->get_name() + "'s turn!");
            client->set_silent(false);
            client->warn("Your turn (" + ci.get_current_character()->get_name() + ')');
            
            if (ci.get_current_character()->get_color() != NONE) {
                auto& p = client->get_player();
                int amount = p.get_built_buildings().count_color(ci.get_current_character()->get_color());
                p.get_wallet().add(amount);
                client->warn("Building income: " + std::to_string(amount) + " gold", true);
            }
            if (ci.get_current_character()->is_robbed()) {
                client->warn("You've been robbed!");
            }
            
            return;
        }
    }
    
    void character_action_turn::on_leave()
    {
        turn::on_leave();
        
        auto&g = get_context().get_game();
        if (!g.is_last_round()) {
            auto tup = g.get_player_with_most_buildings();
            if (std::get<1>(tup) >= 8) {
                g.set_last_round(true);
                
                auto& p = std::get<0>(tup);
                p->set_first_eight(true);
                
                log(INFO) << "Player '" << p->get_name() << "' was the first player to build eight buildings";
            }
        }
    }
}
