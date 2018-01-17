#ifndef magier_h
#define magier_h

#include "character_card.hpp"

namespace machiavelli
{
    class magier : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        magier() : character_card{"Magier", NONE, 3} {}
    };
}

#endif
