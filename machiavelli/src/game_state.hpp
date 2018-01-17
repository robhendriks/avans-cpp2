#ifndef game_state_h
#define game_state_h

#include <string>
#include "command_handler.hpp"

namespace machiavelli
{
    class game_state_manager;
    class game_state
    {
        game_state_manager& m_context;
        std::string m_name;
        std::vector<std::string> m_command_names;
    public:
        game_state(game_state_manager& context, const std::string& name) : m_context{context}, m_name{name} {}
        ~game_state() {} 
        
        void add_commands();
        void remove_commands();
        virtual void register_commands() {}
        
        virtual void on_enter();
        virtual void on_leave();
        
        virtual void on_client_enter(command_sender& client) {}
        virtual void on_client_leave(command_sender& client) {}
        virtual void on_client_command(command_sender& sender, const std::string& cmd);        
        virtual bool accept_client() const { return false; }
        
        game_state_manager& get_context() const { return m_context; }
        std::string get_name() const { return m_name; }
    };
}

#endif
