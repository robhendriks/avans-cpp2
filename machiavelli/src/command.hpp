#ifndef command_h
#define command_h

#include <string>
#include <regex>
#include <vector>
#include <functional>

#include "string_utils.hpp"
#include "command_error.hpp"

namespace machiavelli
{
    class client_info;
    
    using command_args = std::vector<std::string>;
    using command_sender = client_info;
    using command_callback = std::function<bool(command_sender&, const command_args&)>;
    
    class command : public string_utils::string_convertible
    {
        std::string m_name;
        std::string m_description;
        std::string m_usage;
        command_callback m_callback;
        bool m_visible;
        
        inline void check_name(const std::string& s)
        {
            static std::regex e{"^[a-z]+(_[a-z]+)*$"};
            if (!std::regex_match(s, e)) {
                throw std::invalid_argument{"invalid command name '" + s + '\''};
            }
        }
        
    public:
        command() : m_visible{true} {}
        
        bool run(command_sender& sender, const command_args& args);
        
        bool operator()(command_sender& sender, const command_args& args) { return run(sender, args); }
        
        std::string get_name() const { return m_name; }
        void set_name(const std::string &name) { check_name(name); m_name = name; }
        std::string get_description() const { return m_description; }
        void set_description(const std::string &description) { m_description = description; }
        std::string get_usage() const { return m_usage; }
        void set_usage(const std::string &usage) { m_usage = usage; }
        command_callback get_callback() const { return m_callback; }
        void set_callback(command_callback callback) { m_callback = callback; }
        bool is_visible() const { return m_visible; }
        void set_visible(bool visible) { m_visible = visible; }
        
        std::string to_string() const override;
    };
}

#endif
