#ifndef dief_h
#define dief_h

#include "character_card.hpp"

namespace machiavelli
{
    class dief : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        dief() : character_card{"Dief", NONE, 2} {}
    };
}

#endif
