#include "prediker.hpp"
#include "game.hpp"

namespace machiavelli
{
    bool prediker::on_use(game& g, command_sender& sender, const command_args& args)
    {
        throw std::runtime_error{"This character has no action"};
        return true;
    }
}
