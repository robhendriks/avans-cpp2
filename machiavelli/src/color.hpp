#ifndef color_h
#define color_h

#include <functional>
#include "string_utils.hpp"

namespace machiavelli
{
    static const std::vector<std::string> COLOR_STRINGS {"Geel", "Groen", "Blauw", "Rood", "Lila", "None"};
    static const std::vector<std::string> COLOR_ANSI_CODES {"\e[33m", "\e[32m", "\e[34m", "\e[31m", "\e[35m", "\e[0m"};
    
    enum color
    {
        GEEL = 0,
        GROEN = 1,
        BLAUW = 2,
        ROOD = 3,
        LILA = 4,
        NONE = 5
    };
    
    inline color color_from_string(const std::string &str)
    {
        int index = string_utils::find_ignore_case(COLOR_STRINGS, str);
        return index >= 0 ? static_cast<color>(index) : NONE;
    }
    
    inline std::string ansi_code_from_color(color color)
    {
        return COLOR_ANSI_CODES[static_cast<int>(color)];
    }
    
    inline std::string string_from_color(color color)
    {
        return COLOR_STRINGS[static_cast<int>(color)];
    }
    
    inline void for_each_color(std::function<void(color)> cb)
    {
        for (int i = color::GEEL; i != color::NONE; ++i) {
            cb(static_cast<color>(i));
        }
    }
    
    inline bool check_each_color(std::function<bool(color)> cb)
    {
        for (int i = color::GEEL; i != color::NONE; ++i) {
            if (!cb(static_cast<color>(i))) { return false; }
        }
        return true;
    }
}

#endif
