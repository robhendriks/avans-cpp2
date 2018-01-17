#ifndef game_state_play_h
#define game_state_play_h

#include "game_state.hpp"
#include "turn_manager.hpp"
#include "character_iterator.hpp"

namespace machiavelli
{
    class game_state_play : public game_state
    {
        turn_manager m_turn_manager;
        character_iterator m_character_iterator;
    public:
        game_state_play(game_state_manager& context);
        
        void register_commands() override;
        void on_enter() override;
        void on_leave() override;
        
        void on_client_leave(command_sender &client) override;
        
        turn_manager& get_turn_manager() { return m_turn_manager; }
        const turn_manager& get_turn_manager() const { return m_turn_manager; }
        character_iterator& get_character_iterator() { return m_character_iterator; }
        const character_iterator& get_character_iterator() const { return m_character_iterator; }
    };
}

#endif
