#include "command_handler.hpp"

namespace machiavelli
{
    std::string command_handler::suggest(const std::string& name)
    {
        if (m_commands.empty()) { return ""; }
        
        std::vector<std::tuple<int, std::string>> suggestions;
        std::transform(m_commands.begin(), m_commands.end(), std::back_inserter(suggestions), [&name](auto& pair) {
            return std::make_tuple(levenshtein(pair.first, name), pair.first);
        });
        
        auto it = std::remove_if(suggestions.begin(), suggestions.end(), [&](auto& suggestion) {
            return std::get<0>(suggestion) > std::get<1>(suggestion).size() / 2;
        });
        suggestions.erase(it, suggestions.end());
        
        if (suggestions.empty()) { return ""; }
        
        std::sort(suggestions.begin(), suggestions.end(), [&name](auto& a, auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });
        
        return std::get<1>(suggestions.front());
    }
    
    void command_handler::add(const command& cmd)
    {
        auto it = m_commands.find(cmd.get_name());
        if (it != m_commands.end()) {
            throw std::invalid_argument{"duplicate command '" + cmd.get_name() + '\''};
        }
        m_commands.emplace(cmd.get_name(), cmd);
        if (m_tracking) {
//            log(DBG) << "[COMMAND] Registered '" << cmd.get_name() << '\'';
            m_tracked.push_back(cmd.get_name());
        }
    }
    
    void command_handler::remove(const std::string& name)
    {
        auto it = m_commands.find(name);
        if (it == m_commands.end()) {
            throw unknown_command{name, suggest(name)};
        }
        m_commands.erase(it);
    }
    
    command& command_handler::find(const std::string& name)
    {
        auto it = m_commands.find(name);
        if (it == m_commands.end()) {
            throw unknown_command{name, suggest(name)};
        }
        return m_commands[name];
    }
    
    void command_handler::handle(command_sender& sender, const std::string& text)
    {
        command_args args = string_utils::split(text, "\\s+");
        if (args.empty()) {
            throw unknown_command{};
        }
        
        auto& cmd = find(args[0]);
        args.erase(args.begin());
        
        if (!cmd(sender, args)) {
            throw incorrect_command_usage{cmd};
        }
    }
    
    void command_handler::start_tracking()
    {
        if (m_tracking) { throw std::runtime_error{"could not start tracking; invalid tracking state"}; }
        m_tracking = true;
        m_tracked.clear();
//        log(DBG) << "[COMMAND] Begin tracking";
    }
    
    std::vector<std::string> command_handler::stop_tracking()
    {
        if (!m_tracking) { throw std::runtime_error{"could not stop tracking; invalid tracking state"}; }
        m_tracking = false;
//        log(DBG) << "[COMMAND] End tracking";
        return m_tracked;
    }
    
    list_dialog command_handler::get_help_dialog() const
    {
        std::vector<command> results;
        std::transform(m_commands.begin(), m_commands.end(), std::back_inserter(results), [](auto& pair) {
            return pair.second;
        });
        results.erase(std::remove_if(results.begin(), results.end(), [](auto& result) {
            return !result.is_visible();
        }), results.end());
        
        std::vector<std::string> items;
        std::transform(results.begin(), results.end(), std::back_inserter(items), [](auto& result) { return result.to_string(); });
        std::sort(items.begin(), items.end());
        return list_dialog{items};
    }
}
