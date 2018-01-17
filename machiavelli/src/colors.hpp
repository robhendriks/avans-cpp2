#ifndef colors_h
#define colors_h

namespace machiavelli
{
    inline std::string colorize_info(const std::string& str, bool dim = false)
    {
        static std::string color{"\e[38;5;114m"};
        return color + (dim ? "\e[2m" : "") + str;
    }
    
    inline std::string colorize_warning(const std::string& str, bool dim = false)
    {
        static std::string color{"\e[38;5;184m"};
        return color + (dim ? "\e[2m" : "") + str;
    }
    
    inline std::string colorize_error(const std::string& str, bool dim = false)
    {
        static std::string color{"\e[38;5;124m"};
        return color + (dim ? "\e[2m" : "") + str;
    }
}

#endif
