#ifndef turn_manager_h
#define turn_manager_h

#include <memory>
#include "turn.hpp"

namespace machiavelli
{
    using turn_ptr = std::unique_ptr<turn>;
    
    class game;
    class game_state_play;
    class turn_manager
    {
        game& m_game;
        game_state_play& m_state;
        turn_ptr m_turn;
    public:
        turn_manager(game& g, game_state_play& state) : m_game{g}, m_state{state}, m_turn{nullptr} {}
        
        void set_turn(turn_ptr turn);
        
        template<class T>
        void next()
        {
            static_assert(std::is_base_of<turn, T>::value, "!!!");
            set_turn(std::make_unique<T>(*this));
        }
        
        void reset_turn();
        void reset_round();
        
        game& get_game() { return m_game; }
        const game& get_game() const { return m_game; }
        game_state_play& get_state() { return m_state; }
        const game_state_play& get_state() const { return m_state; }
    };
}

#endif
