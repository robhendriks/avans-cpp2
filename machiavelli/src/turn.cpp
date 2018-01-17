#include "turn.hpp"
#include "turn_manager.hpp"
#include "command_handler.hpp"

#include <networking/logging.h>

namespace machiavelli
{
    void turn::add_commands()
    {
        command_handler::get_instance().start_tracking();
        register_commands();
        m_command_names = command_handler::get_instance().stop_tracking();
    }
    
    void turn::remove_commands()
    {
        auto& ch = command_handler::get_instance();
        for (auto& command_name : m_command_names) {
            ch.remove(command_name);
        }
    }
    
    void turn::on_enter()
    {
        log(DBG) << "Entering '" + m_name + "' turn";
        add_commands();
    }
    
    void turn::on_leave()
    {
        log(DBG) << "Leaving '" + m_name + "' turn";
        remove_commands();
    }
}
