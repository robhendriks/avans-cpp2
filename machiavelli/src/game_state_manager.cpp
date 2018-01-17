#include "game_state_manager.hpp"
#include "game_state.hpp"
#include "game.hpp"

namespace machiavelli
{
    void game_state_manager::on_client_enter(command_sender& client)
    {
        if (m_state) { m_state->on_client_enter(client); }
    }
    
    void game_state_manager::on_client_leave(command_sender& client)
    {
        if (m_state) { m_state->on_client_leave(client); }
    }
    
    void game_state_manager::on_client_command(command_sender& sender, const std::string& cmd)
    {
        if (m_state) {
            m_state->on_client_command(sender, cmd);
        }
    }
    
    bool game_state_manager::accept_client() const
    {
        if (m_state) {
            return m_state->accept_client();
        }
        return false;
    }
    
    void game_state_manager::set_state(game_state_ptr state)
    {
        if (m_state) {
            m_state->on_leave();
        }
        m_state = game_state_ptr{std::move(state)};
        if (m_state) {
            m_state->on_enter();
        }
    }
}
