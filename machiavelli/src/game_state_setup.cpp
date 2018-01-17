#include "game_state_setup.hpp"
#include "game_state_manager.hpp"
#include "game_state_lobby.hpp"
#include "game_state_play.hpp"
#include "game.hpp"
#include "random_utils.hpp"
#include "list_dialog.hpp"
#include "koning.hpp"

namespace machiavelli
{    
    void game_state_setup::on_enter()
    {
        game_state::on_enter();
        
        // ez fam
        auto& g = get_context().get_game();
        g.for_each_client([](client_info& client) {
            client.clear();
        });
        
        g.warn("Setting up game...", true);
        g.pick_king();
        
        g.for_each_client([&g](client_info& client) {
            for (int i = 0; i < 4; ++i) {
                client.get_player()
                    .get_buildings()
                    .push(g.get_buildings().pop_random());
            }
            
            client.get_player().get_wallet().add(2);
        });
        
        get_context().next<game_state_play>();
    }
    
    void game_state_setup::on_leave()
    {
        game_state::on_leave();
    }
    
    void game_state_setup::on_client_leave(command_sender& client)
    {
        get_context().next<game_state_lobby>();
    }
}
