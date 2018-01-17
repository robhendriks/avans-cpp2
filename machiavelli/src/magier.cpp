#include "magier.hpp"
#include "game.hpp"

namespace machiavelli
{
    bool magier::on_use(game& g, command_sender& sender, const command_args& args)
    {
        if (args.empty()) {
            auto other = g.peek_player();
            other->get_player().get_buildings().swap(sender.get_player().get_buildings());
            
            sender.info("Swapped building cards with '" + other->get_player().get_display_name() + '\'');
            other->warn("Swapped building cards with '" + sender.get_player().get_display_name() + '\'');
        } else {
            command_args ids{args};
            std::sort(ids.begin(), ids.end(), [](auto a, auto b) {
                return std::stoi(a) < std::stoi(b);
            });
            
            auto& global_buildings = g.get_buildings();
            auto& player_buildings = sender.get_player().get_buildings();
            
            card_deck<building_card> tmp;
            
            int count = 0;
            int count_succes = 0;
            for (auto id : ids) {
                int i = std::stoi(id);
                try {
                    tmp.push_back(player_buildings.pop_at(i - count));
                    player_buildings.push_back(global_buildings.pop());
                    ++count_succes;
                } catch (...) {
                    log(WARN) << "Invalid ID '" + id + '\'';
                }
                ++count;
            }
            
            tmp.transfer_back(global_buildings);
            sender.info("Swapped " + std::to_string(count_succes) + " building card(s)");
        }
        
        return true;
    }
}
