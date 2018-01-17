#ifndef moordenaar_h
#define moordenaar_h

#include "character_card.hpp"

namespace machiavelli
{
    class moordenaar : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        moordenaar() : character_card{"Moordenaar", NONE, 1} {}
    };
}

#endif
