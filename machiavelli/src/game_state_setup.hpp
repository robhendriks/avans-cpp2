#ifndef game_state_setup_h
#define game_state_setup_h

#include "game_state.hpp"

namespace machiavelli
{
    class game_state_setup : public game_state
    {
    protected:
        void pick_king();
        
    public:
        game_state_setup(game_state_manager& context) : game_state{context, "setup"} {}
        
        void on_enter() override;
        void on_leave() override;
        void on_client_leave(command_sender& client) override;
    };
}

#endif

