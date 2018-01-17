#ifndef character_action_turn_h
#define character_action_turn_h

#include "turn.hpp"

namespace machiavelli
{
    class character_action_turn : public turn
    {
    public:
        character_action_turn(turn_manager& context) : turn{context, "character_action"} {}
        
        void register_commands() override;
        
        void on_enter() override;
        void on_leave() override;
    };
}

#endif
