#ifndef game_h
#define game_h

#include <set>
#include <mutex>
#include <memory>

#include "card_manager.hpp"
#include "command_handler.hpp"
#include "client_info.hpp"
#include "client_command.hpp"
#include "game_state_manager.hpp"
#include "options.hpp"

#define VARS_FILE_NAME "vars.json"

namespace machiavelli
{
    class server;
    class game_state_manager;
    class game
    {
        friend class server;
        
        server& m_server;
        options m_vars;
        game_state_manager m_state_manager;
        card_manager m_card_manager;
        std::mutex m_mutex;
        std::set<std::shared_ptr<client_info>> m_clients;
        std::shared_ptr<client_info> m_current_player;
        card_deck<character_card> m_characters;
        card_deck<building_card> m_buildings;
        bool m_last_round;
        
        void init();
        void deinit();
        void return_to_lobby();
        void reset_clients();
    public:
        game(server& s, options& vars) : m_server{s}, m_vars{vars}, m_state_manager{*this}, m_card_manager{}, m_last_round{false} { init(); }
        ~game() { deinit(); }
        
        void reset();
        void reset_characters();
        void reset_player_characters();
        void remove_top_character();
        void set_new_king(std::shared_ptr<client_info> new_king);
        std::shared_ptr<client_info> find_new_king();
        std::shared_ptr<client_info> pick_new_king();
        void pick_king();
        
        void join(std::shared_ptr<client_info> client);
        void leave(std::shared_ptr<client_info> client);
        
        void on_command(const client_command& cmd);
        
        void send(std::shared_ptr<client_info> client, const std::string& msg);
        void broadcast(const std::string& msg);
        void info(const std::string& msg, bool dim = false);
        void warn(const std::string& msg, bool dim = false);
        void error(const std::string& msg, bool dim = false);
        
        void for_each_client(std::function<void(client_info&)> callback);
        
        options& get_vars() { return m_vars; }
        const options& get_vars() const { return m_vars; }
        
        game_state_manager& get_state_manager() { return m_state_manager; }
        const game_state_manager& get_state_manager() const { return m_state_manager; }
        
        std::set<std::shared_ptr<client_info>>& get_clients() { return m_clients; }
        size_t get_client_count();
        std::shared_ptr<client_info> get_client_by_player_name(const std::string& name);
        std::shared_ptr<character_card> get_character_by_name(const std::string& name);
        
        bool player_name_available(const std::string& name);
        
        std::shared_ptr<client_info> get_king();
        std::shared_ptr<client_info> peek_player();
        std::shared_ptr<client_info> get_current_player() { return m_current_player; }
        void set_current_player(std::shared_ptr<client_info> current_player);
        void advance_player();
        
        card_deck<character_card>& get_characters() { return m_characters; }
        card_deck<building_card>& get_buildings() { return m_buildings; }
        
        std::mutex& get_mutex() { return m_mutex; };
        
        bool is_last_round() const { return m_last_round; }
        void set_last_round(bool last_round) { m_last_round = last_round; }
        
        std::tuple<player*, int> get_player_with_most_buildings();
        std::vector<stats> get_stats();
    };
}

#endif
