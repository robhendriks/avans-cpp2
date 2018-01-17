#ifndef game_state_lobby_h
#define game_state_lobby_h

#include "game_state.hpp"

namespace machiavelli
{
    class game_state_lobby : public game_state
    {
    public:
        game_state_lobby(game_state_manager& context) : game_state{context, "lobby"} {}
        
        void register_commands() override;
        
        void on_enter() override;
        void on_leave() override;
        
        void on_client_enter(command_sender& client) override;
        void on_client_leave(command_sender& client) override;
        
        bool accept_client() const override { return true; }
    };
}

#endif
