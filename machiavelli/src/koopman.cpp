#include "koopman.hpp"
#include "game.hpp"

namespace machiavelli
{
    bool koopman::on_use(game& g, command_sender& sender, const command_args& args)
    {
        sender.get_player().get_wallet().add(1);
        sender.info("You've earned 1 gold");
        return true;
    }
}
