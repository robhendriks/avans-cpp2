#include "dief.hpp"
#include "game.hpp"
#include "character_card_factory.hpp"

namespace machiavelli
{
    bool dief::on_use(game& g, command_sender& sender, const command_args& args)
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
            throw std::runtime_error{"You cannot rob yourself"};
        } else if (!character->is_alive()) {
            throw std::runtime_error{"You cannot rob a dead character"};
        } else if (character->get_id() == 1) {
            throw std::runtime_error{"You cannot rob the 'Moordenaar'"};
        }
        
        int old_balance = sender.get_player().get_wallet().get_balance();
        character->rob(sender);
        int new_balance = sender.get_player().get_wallet().get_balance();
        
        sender.info("You've stolen " + std::to_string(new_balance - old_balance) + " gold");
        return true;
    }
}
