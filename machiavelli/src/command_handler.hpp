#ifndef command_handler_h
#define command_handler_h

#include <map>
#include <vector>
#include <tuple>
#include <stdexcept>
#include "command.hpp"
#include "levenstein.hpp"
#include "list_dialog.hpp"

namespace machiavelli
{
    using command_map = std::map<std::string, command>;
    
    class command_handler
    {
        bool m_tracking;
        std::vector<std::string> m_tracked;
        command_map m_commands;
        
        command_handler() : m_commands{} {}
        
        std::string suggest(const std::string& name);
    public:
        command_handler(const command_handler&) = delete;
        command_handler& operator=(const command_handler&) = delete;
        
        static command_handler& get_instance()
        {
            static command_handler instance;
            return instance;
        }
        
        void add(const command& cmd);
        void remove(const std::string& name);
        command& find(const std::string& name);
        void handle(command_sender& sender, const std::string& text);
        
        void start_tracking();
        std::vector<std::string> stop_tracking();
        
        list_dialog get_help_dialog() const;
    };
}

#endif
