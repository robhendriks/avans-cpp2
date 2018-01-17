#ifndef string_utils_h
#define string_utils_h

#include <string>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>
#include "string_convertible.hpp"

namespace machiavelli
{
    namespace string_utils
    {
        inline void clean(std::string& str)
        {
            str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
                return c == '\n' || c == '\r';
            }));
        }
        
        inline std::string clean_copy(std::string str)
        {
            clean(str);
            return str;
        }
        
        inline void to_lower_case(std::string& str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        }
        
        inline std::string to_lower_case_copy(std::string str)
        {
            to_lower_case(str);
            return str;
        }
        
        inline void to_upper_case(std::string& str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        }
        
        inline std::string to_upper_case_copy(std::string str)
        {
            to_upper_case(str);
            return str;
        }
        
        inline int find_ignore_case(const std::vector<std::string> &haystack, std::string needle)
        {
            to_lower_case(needle);
            
            auto it = std::find_if(haystack.begin(), haystack.end(), [&](const std::string &str) {
                return to_lower_case_copy(str) == needle;
            });
            
            if (it == haystack.end()) {
                return -1;
            }
            
            return static_cast<int>(std::distance(haystack.begin(), it));
        }
        
        inline std::vector<std::string> split(const std::string& str, const std::string& regex_str)
        {
            std::regex re(regex_str);
            std::sregex_token_iterator first{str.begin(), str.end(), re, -1}, last;
            return {first, last};
        }
        
        inline std::string join(const std::vector<std::string>& strs, const char delimiter)
        {            
            std::stringstream ss;
            for (auto it = strs.begin(); it != strs.end(); ++it) {
                if (it != strs.begin()) { ss << delimiter; }
                ss << *it;
            }
            return ss.str();
        }
        
        inline std::string strip_ansi(const std::string& str)
        {
            static std::regex re{"[\\u001B\\u009B][[\\]()#;?]*(?:(?:(?:[a-zA-Z\\d]*(?:;[a-zA-Z\\d]*)*)?\\u0007)|(?:(?:\\d{1,4}(?:;\\d{0,4})*)?[\\dA-PRZcf-ntqry=><~]))"};
            
            std::string result;
            std::regex_replace(std::back_inserter(result), str.begin(), str.end(), re, "");
            return result;
        }
        
        inline bool is_snake_case(const std::string& str)
        {
            static std::regex e{"^[A-Za-z0-9]+(_[A-Za-z0-9]+)*$"};
            return std::regex_match(str, e);
        }
    }
}

#endif
