#include "game_state.hpp"
#include "game_state_manager.hpp"
#include "game.hpp"

#include <networking/logging.h>

namespace machiavelli
{
    void game_state::add_commands()
    {
        command_handler::get_instance().start_tracking();
        register_commands();
        m_command_names = command_handler::get_instance().stop_tracking();
    }
    
    void game_state::remove_commands()
    {
        auto& ch = command_handler::get_instance();
        for (auto& command_name : m_command_names) {
            ch.remove(command_name);
        }
    }
    
    void game_state::on_enter()
    {
        log(DBG) << "Entering '" << m_name << "' state";
        add_commands();
    }
    
    void game_state::on_leave()
    {
        log(DBG) << "Leaving '" << m_name << "' state";
        remove_commands();
    }
    
    void game_state::on_client_command(command_sender& sender, const std::string& text)
    {        
        try {
            log(INFO) << "[COMMAND] [" << sender.get_player().get_name() << "] " + text;
            command_handler::get_instance().handle(sender, text);
        } catch (const std::exception& e) {
            sender.error(e.what());
            log(ERROR) << "[COMMAND] [" << sender.get_player().get_name() << "] " << std::string(e.what());
        } catch (...) {
            log(ERROR) << "[COMMAND] [" << sender.get_player().get_name() << "] Unknown error";
        }
    }
}
