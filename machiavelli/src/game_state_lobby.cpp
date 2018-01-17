#include "game_state_lobby.hpp"
#include "game_state_manager.hpp"
#include "game_state_setup.hpp"
#include "game.hpp"
#include "list_dialog.hpp"
#include "command_builder.hpp"

namespace machiavelli
{
    void game_state_lobby::register_commands()
    {
        register_command()
            .name("start")
            .description("start the game")
            .callback([this](command_sender& sender, const command_args& args) {
                if (get_context().get_game().get_client_count() != 2) {
                    throw std::runtime_error{"incorrect number of players; must be exactly 2"};
                }
                get_context().next<game_state_setup>();
                return true;
            });
    }
    
    void game_state_lobby::on_enter()
    {
        game_state::on_enter();
        
        auto& game = get_context().get_game();
        game.reset();
        
        game.warn("Returning to lobby", true);
    }
    
    void game_state_lobby::on_leave()
    {
        game_state::on_leave();
    }
    
    void game_state_lobby::on_client_enter(command_sender& client)
    {
        auto& game = get_context().get_game();
        
        if (game.get_clients().size() == 2) {
            game.warn("Enough players, type 'start' proceed", true);
        }
    }
    
    void game_state_lobby::on_client_leave(command_sender& client)
    {
    }
}
