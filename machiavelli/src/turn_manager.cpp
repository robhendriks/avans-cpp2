#include "turn_manager.hpp"
#include "game.hpp"
#include "game_state_play.hpp"

namespace machiavelli
{
    void turn_manager::reset_turn()
    {
        m_game.for_each_client([](auto& client) {
            client.get_player().reset_turn();
        });
    }
    
    void turn_manager::reset_round()
    {
        get_state().get_character_iterator().reset();
     
        m_game.pick_king();
        m_game.reset_characters();
        
        m_game.for_each_client([](auto& client) {
            client.get_player().reset_round();
        });
    }
    
    void turn_manager::set_turn(turn_ptr turn)
    {
        if (m_turn) {
            m_turn->on_leave();
        }
        m_turn = turn_ptr{std::move(turn)};
        if (m_turn) {
            m_turn->on_enter();
        }
    }
}
