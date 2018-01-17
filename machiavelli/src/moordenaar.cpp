#include "moordenaar.hpp"
#include "game.hpp"
#include "character_card_factory.hpp"

namespace machiavelli
{
    bool moordenaar::on_use(game& g, command_sender& sender, const command_args& args)
    {
        if (args.size() < 1) {
            throw std::runtime_error{"Usage: use <character>"};
        } else if (!character_card_factory::get_instance().character_exists(args[0])) {
            throw std::runtime_error{"Unknown character '" + args[0] + '\''};
        }
        
        std::shared_ptr<character_card> character{nullptr};
        try {
            character = g.get_character_by_name(args[0]);
        } catch (...) {
            sender.info("\e[38;5;108mSpecial used");
            return true;
        }
        
        if (character->get_owner()->get_player() == sender.get_player()) {
            throw std::runtime_error{"You cannot kill yourself"};
        }
        
        character->kill();
        sender.info("\e[38;5;108mSpecial used");
        
        return true;
    }
}
