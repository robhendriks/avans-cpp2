#ifndef bouwmeester_h
#define bouwmeester_h

#include "character_card.hpp"

namespace machiavelli
{
    class bouwmeester : public character_card
    {
    protected:
        bool on_use(game& g, command_sender& sender, const command_args& args) override;
    public:
        bouwmeester() : character_card{"Bouwmeester", NONE, 7} {}

        int max_build_count() const override { return 3; }
    };
}

#endif
