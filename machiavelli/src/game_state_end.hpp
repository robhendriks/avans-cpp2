#ifndef game_state_end_h
#define game_state_end_h

#include "game_state.hpp"

namespace machiavelli
{
    class game_state_end : public game_state
    {
    public:
        game_state_end(game_state_manager& context) : game_state{context, "end"} {}
        
        void on_enter() override;
    };
}

#endif
