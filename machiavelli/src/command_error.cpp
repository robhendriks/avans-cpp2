#include "command_error.hpp"
#include "command.hpp"

namespace machiavelli
{
    const char* incorrect_command_usage::what() const noexcept
    {
        std::string s{"usage: "};
        if (!m_command.get_usage().empty()) {
            return (s + m_command.get_usage()).c_str();
        }
        return (s + m_command.get_name()).c_str();
    }
    
    const char* unknown_command::what() const noexcept
    {
        std::string s{"unknown command"};
        if (!m_name.empty()) {
            s += " '" + m_name + '\'';
        }
        if (!m_suggestion.empty()) {
            s += ", did you mean '" + m_suggestion + '\'';
        }
        return s.c_str();
    }
}
