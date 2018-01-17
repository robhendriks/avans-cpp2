#ifndef command_builder_h
#define command_builder_h

#include "command_handler.hpp"

namespace machiavelli
{
    class command_builder
    {
        command m_command;
    public:
        command_builder() {}
        ~command_builder();
        
        command_builder& name(const std::string& value);
        command_builder& description(const std::string& value);
        command_builder& usage(const std::string& value);
        command_builder& callback(command_callback value);
        command_builder& visible(bool value);
    };
    
    inline command_builder register_command()
    {
        return command_builder{};
    }
}

#endif
