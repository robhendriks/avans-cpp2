#ifndef game_state_manager_h
#define game_state_manager_h

#include <memory>
#include "game_state.hpp"
#include "command_handler.hpp"

namespace machiavelli
{
    using game_state_ptr = std::unique_ptr<game_state>;
    
    class game;
    class game_state_manager
    {
        game& m_game;
        game_state_ptr m_state;
    public:
        game_state_manager(game& g) : m_game{g}, m_state{nullptr} {}
        
        void on_client_enter(command_sender& client);
        void on_client_leave(command_sender& client);
        void on_client_command(command_sender& sender, const std::string& cmd);
        bool accept_client() const;
        
        game& get_game() const { return m_game; }
        void set_state(game_state_ptr state);
        
        template<class T>
        void next()
        {
            static_assert(std::is_base_of<game_state, T>::value, "!!!");
            set_state(std::make_unique<T>(*this));
        }
    };
}

#endif
