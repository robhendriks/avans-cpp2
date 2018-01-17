#include "condottiere.hpp"
#include "game.hpp"
#include "prediker.hpp"

namespace machiavelli
{
    bool condottiere::on_use(game& g, command_sender& sender, const command_args& args)
    {
        if (args.size() < 1) {
            throw std::runtime_error{"Usage: use <building_card_index>"};
        }
        
        auto client = g.peek_player();
        
        auto& source_player = sender.get_player();
        auto& target_player = client->get_player();
        
        if (target_player.get_built_buildings().size() >= 8) {
            throw std::runtime_error{"You cannot destroy a building in a city with 8 or more buildings"};
        } else if (target_player.get_characters().has<prediker>()) {
            throw std::runtime_error{"You cannot destroy a building that belongs to a prediker"};
        }
        
        int i = std::stoi(args[0]);
        
        auto card = target_player.get_built_buildings().peek_at(i);
        source_player.get_wallet().remove(card->get_destroy_cost());
        card = target_player.get_built_buildings().pop_at(i);
        g.get_buildings().push_back(card);
        
        g.warn(source_player.get_display_name() + " destroyed " + target_player.get_display_name() + "'s " + card->get_name());
        
        return true;
    }
}
