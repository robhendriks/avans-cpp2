#include "game_state_end.hpp"
#include "game_state_manager.hpp"
#include "game.hpp"
#include "command_builder.hpp"
#include "game_state_lobby.hpp"

namespace machiavelli
{
    void game_state_end::on_enter()
    {
        game_state::on_enter();
        
        auto& g = get_context().get_game();
        g.for_each_client([](auto& client) {
            client.clear();
        });
        
        auto all_stats = g.get_stats();
        if (all_stats.size() != 2) throw std::runtime_error{"Unexpected error"};
        
        auto&a = all_stats.at(0);
        auto&b = all_stats.at(1);
        
        bool tie = a.get_total_score() == b.get_total_score();
        int winner = -1;
        if (tie) {
            winner = a.get_building_score() > b.get_building_score() ? 0 : 1;
        } else {
            winner = a.get_total_score() > b.get_total_score() ? 0 : 1;
        }
        
        int i = 0;
        for (auto stats : all_stats) {
            g.warn((i == winner ? "WINNER! " : "") + stats.get_player().get_display_name());
            g.broadcast(stats.to_string() + "\r\n");
            ++i;
        }
        
        get_context().next<game_state_lobby>();
    }
}
