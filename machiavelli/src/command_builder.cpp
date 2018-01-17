#include "command_builder.hpp"

namespace machiavelli
{
    command_builder::~command_builder()
    {
        command_handler::get_instance().add(m_command);
    }
    
    command_builder& command_builder::name(const std::string& value)
    {
        m_command.set_name(value);
        return *this;
    }
    
    command_builder& command_builder::description(const std::string& value)
    {
        m_command.set_description(value);
        return *this;
    }
    
    command_builder& command_builder::usage(const std::string& value)
    {
        m_command.set_usage(value);
        return *this;
    }
    
    command_builder& command_builder::callback(command_callback value)
    {
        m_command.set_callback(value);
        return *this;
    }
    
    command_builder& command_builder::visible(bool value)
    {
        m_command.set_visible(value);
        return *this;
    }
}
