#ifndef server_h
#define server_h

#include <thread>
#include <vector>
#include <chrono>
#include <networking/Socket.h>
#include <networking/Sync_queue.h>

#include "game.hpp"
#include "client_info.hpp"
#include "client_command.hpp"
#include "string_utils.hpp"
#include "options.hpp"

namespace machiavelli
{
    class server : public string_utils::string_convertible
    {
        static const int s_port;
        
        bool m_running;
        size_t m_player_count;
        game m_game;
        ServerSocket m_socket;
        Sync_queue<client_command> m_command_queue;
        std::vector<std::thread> m_client_threads;
        std::string m_motd;
        
        void init();
        void handle_connection(Socket socket);
        void consume_commands();
        void cleanup();
    public:
        server(options& vars) : m_running{true}, m_player_count{0}, m_game{*this, vars}, m_socket{s_port}, m_client_threads{} {}
        
        void start();
        void stop();
        
        bool is_running() const { return m_running; }
        std::string get_motd() const { return m_motd; }
        
        std::string to_string() const override;
    };
}

#endif
