#include <networking/logging.h>

#include <fstream>
#include "server.hpp"

namespace machiavelli
{
    const int server::s_port = 1080;
    
    void server::init()
    {        
        std::ifstream is{"data/motd.txt"};
        m_motd = std::string{std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()};
        
        std::thread command_thread{&server::consume_commands, this};
        command_thread.detach();
    }
    
    void server::handle_connection(Socket socket)
    {
        ++m_player_count;
        
        auto client = std::make_shared<client_info>(std::move(socket), player{"player" + std::to_string(m_player_count)});
        m_game.join(client);
        
        try {
            while (m_running && !client->should_quit()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                
                try {
                    std::string cmd;
                    bool succes = client->get_socket().readline([&cmd](std::string str) {
                        cmd = str;
                    });
                    
                    if (!succes) { continue; }
                    
                    client_command command{cmd, client};
                    m_command_queue.put(command);
                } catch (const std::exception& e) {
                    log(ERROR) << "Error: " << e.what();
                } catch (...) {
                    log(ERROR) << "Unexpected error";
                }
            }
            
            if (m_running) {
                m_game.leave(client);
            }
        } catch (const std::exception& e) {
            log(ERROR) << "Error in handle_connection() - " << e.what();
        } catch (...) {
            log(ERROR) << "Error in handle_connection()";
        }
    }
    
    void server::consume_commands()
    {
        while (m_running) {
            try {
                client_command cm = m_command_queue.get();
                if (!m_running) {
                    break;
                }
                m_game.on_command(cm);
            } catch (const std::exception &ex) {
                
            } catch (...) {
                
            }
        }
    }
    
    void server::cleanup()
    {
        log(INFO) << "Cleaning up...";
        
        for (auto& client_thread : m_client_threads) {
            client_thread.join();
        }
    }
    
    void server::start()
    {
        init();
        
        try {
            log(INFO) << "Listening on port " << s_port;
            
            while (m_running) {                
                m_socket.accept([this](Socket socket) {
                    log(INFO) << "Connection from " << socket.get_dotted_ip() << ":" << socket.get_port();
                    
                    if (!m_game.get_state_manager().accept_client()) {
                        socket << "Game in progress\r\n";
                        return;
                    }
                    
                    std::thread client_thread{&server::handle_connection, this, std::move(socket)};
                    client_thread.detach();
                });
                
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        } catch (const std::exception& e) {
            log(ERROR) << "Error in start() - " << e.what();
        } catch (...) {
            log(ERROR) << "Error in start()";
        }
        
        cleanup();
    }
    
    void server::stop()
    {
        if (m_running) {
            m_running = false;
        }
    }
    
    std::string server::to_string() const
    {
        throw std::runtime_error{"not implemented"};
    }
}
