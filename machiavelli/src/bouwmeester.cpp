#include "bouwmeester.hpp"
#include "game.hpp"

namespace machiavelli
{
    bool bouwmeester::on_use(game& g, command_sender& sender, const command_args& args)
    {
        card_deck<building_card> tmp;
        for (int i = 0; i < 2; ++i) {
            tmp.push(g.get_buildings().pop());
        }

        sender.show(tmp);
        tmp.transfer(sender.get_player().get_buildings());
        
        return true;
    }
}
