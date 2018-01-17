#ifndef koopman_h
#define koopman_h

#include "character_card.hpp"

namespace machiavelli
{
    class koopman : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        koopman() : character_card{"Koopman", GROEN, 6} {}
    };
}

#endif
