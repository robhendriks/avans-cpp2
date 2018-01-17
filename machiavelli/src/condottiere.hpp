#ifndef condottiere_h
#define condottiere_h

#include "character_card.hpp"

namespace machiavelli
{
    class condottiere : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        condottiere() : character_card{"Condottiere", ROOD, 8} {}
    };
}

#endif
