#ifndef character_setup_turn_h
#define character_setup_turn_h

#include "turn.hpp"

namespace machiavelli
{
    class character_setup_turn : public turn
    {
    public:
        character_setup_turn(turn_manager& context) : turn{context, "character_setup"} {}
        
        void register_commands() override;
        
        void on_enter() override;
        void on_leave() override;
    };
}

#endif
