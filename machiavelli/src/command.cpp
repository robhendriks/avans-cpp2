#include "command.hpp"
#include "client_info.hpp"

namespace machiavelli
{
    bool command::run(command_sender& sender, const command_args& args)
    {
        return m_callback(sender, args);
    }
    
    std::string command::to_string() const
    {
        std::stringstream ss;
        ss << "\e[1m" << m_name;
        if (!m_usage.empty()) {
            ss << "\e[0m " << m_usage;
        }
        
        if (!m_description.empty()) {
            ss << "\e[0m\e[2m : " << m_description;
        }
        
        return ss.str();
    }
}
