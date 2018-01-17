#ifndef koning_h
#define koning_h

#include "character_card.hpp"

namespace machiavelli
{
    class koning : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        koning() : character_card{"Koning", GEEL, 4} {}
    };
}

#endif
