#include "character_setup_turn.hpp"
#include "character_pick_turn.hpp"
#include "turn_manager.hpp"
#include "game.hpp"
#include "command_builder.hpp"

namespace machiavelli
{
    void character_setup_turn::register_commands()
    {
    }
    
    void character_setup_turn::on_enter()
    {
        turn::on_enter();
        
        // Reset characters deck
        auto& g = get_context().get_game();
        
        g.reset_player_characters();
        g.remove_top_character();
        
        get_context().next<character_pick_turn>();
    }
    
    void character_setup_turn::on_leave()
    {
        turn::on_leave();
    }
}
