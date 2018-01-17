#ifndef command_error_h
#define command_error_h

#include <string>
#include <stdexcept>
namespace machiavelli
{
    class command;
    class command_error : public std::runtime_error
    {
    public:
        command_error() : std::runtime_error{""} {}
    };
    
    class incorrect_command_usage : public command_error
    {
        const command& m_command;
    public:
        incorrect_command_usage(const command& c) : m_command{c} {}
        
        const command& get_command() const { return m_command; }
        
        const char* what() const noexcept override;
    };
    
    class unknown_command : public command_error
    {
        std::string m_name;
        std::string m_suggestion;
    public:
        unknown_command(const std::string& name, const std::string& suggestion) : m_name{name}, m_suggestion{suggestion} {}
        unknown_command(const std::string& name) : unknown_command{name, ""} {}
        unknown_command() : unknown_command{""} {}
        
        const char* what() const noexcept override;
    };
}

#endif
