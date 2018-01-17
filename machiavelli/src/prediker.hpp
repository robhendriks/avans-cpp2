#ifndef prediker_h
#define prediker_h

#include "character_card.hpp"

namespace machiavelli
{
    class prediker : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        prediker() : character_card{"Prediker", BLAUW, 5} {}
        
        bool can_destroy() const override { return false; }
    };
}

#endif
