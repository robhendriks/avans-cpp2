#ifndef pick_character_turn_h
#define pick_character_turn_h

#include "turn.hpp"

namespace machiavelli
{
    class character_pick_turn : public turn
    {
    public:
        character_pick_turn(turn_manager& context);

        void register_commands() override;

        void on_enter() override;
        void on_leave() override;
    };
}

#endif
