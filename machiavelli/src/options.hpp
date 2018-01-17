#ifndef options_h
#define options_h

#include <string>
#include <map>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include "string_utils.hpp"

namespace machiavelli
{
    class option
    {
        int m_value;
    public:
        option(int value) : m_value{value} {}
        
        void operator=(int value) { set_value(value); }
        
        int get_value() const { return m_value; }
        void set_value(int value) { m_value = value; }
    };
    
    class options : public string_utils::string_convertible
    {
        using key_t = std::string;
        using value_t = option;
        
        std::map<key_t, value_t> m_options;
        
        void fill(std::initializer_list<std::pair<key_t, int>> il);
        void fail(const key_t& key) const;
    public:
        options() {}
        options(std::initializer_list<std::pair<key_t, int>> il) { fill(il); }
        
        void load(const std::string& file_name);
        void save(const std::string& file_name) const;
        void save_default(const std::string& file_name) const;
        
        int get(const key_t& key) const;
        void set(const key_t& key, int value);
        bool is_set(const key_t& key) const;
        bool is_true(const key_t& key) const;
        bool is_false(const key_t& key) const;
        
        decltype(auto) begin() { return m_options.begin(); }
        decltype(auto) begin() const { return m_options.begin(); }
        decltype(auto) end() { return m_options.end(); }
        decltype(auto) end() const { return m_options.end(); }
        
        std::string to_string() const;
    };
    
    inline bool file_exists(const std::string& file_name)
    {
        return access(file_name.c_str(), F_OK) != -1;
    }
}

#endif
