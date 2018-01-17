#include "options.hpp"
#include <sstream>
#include <json.hpp>
#include <networking/logging.h>

using namespace nlohmann;

namespace machiavelli
{
    void options::fill(std::initializer_list<std::pair<key_t, int>> il)
    {
        for (auto& pair : il) {
            m_options.emplace(pair.first, option{pair.second});
        }
    }
    
    void options::fail(const key_t& key) const
    {
        throw std::invalid_argument{"unknown key '" + key + '\''};
    }
    
    void options::load(const std::string& file_name)
    {
        std::ifstream is{file_name};
        if (!is.is_open()) {
            throw std::runtime_error{"file not found '" + file_name + '\''};
        }
        
        json j;
        is >> j;
        
        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            const key_t key = it.key();
            const value_t value = option{it.value().get<int>()};
            
            log(INFO) << "Server var '" + key + "' set to '" + std::to_string(value.get_value()) + '\'';
        }
    }
    
    void options::save(const std::string& file_name) const
    {
        std::ofstream os{file_name};
        
        nlohmann::json j;
        for (auto& pair : m_options) {
            j[pair.first] = pair.second.get_value();
        }
        os << std::setw(4) << j;
    }
    
    void options::save_default(const std::string& file_name) const
    {
        if (!file_exists(file_name)) {
            save(file_name);
        }
    }
    
    int options::get(const key_t& key) const
    {
        auto it = m_options.find(key);
        if (it == m_options.end()) { fail(key); }
        return it->second.get_value();
    }
    
    void options::set(const key_t& key, int value)
    {
        auto it = m_options.find(key);
        if (it == m_options.end()) { fail(key); }
        it->second.set_value(value);
    }
    
    bool options::is_set(const key_t& key) const
    {
        return m_options.find(key) != m_options.end();
    }
    
    bool options::is_true(const key_t& key) const
    {
        auto it = m_options.find(key);
        if (it == m_options.end()) { fail(key); }
        return it->second.get_value() > 0;
    }
    
    bool options::is_false(const key_t& key) const
    {
        return !is_true(key);
    }
    
    std::string options::to_string() const
    {
        std::stringstream ss;
        for (auto it = m_options.begin(); it != m_options.end(); ++it) {
            auto& pair = *it;
            if (it != m_options.begin()) { ss << "\r\n"; }
            ss << "\e[2m - \e[0m" << pair.first << " \e[2m:\e[0m " << pair.second.get_value();
        }
        return ss.str();
    }
}
