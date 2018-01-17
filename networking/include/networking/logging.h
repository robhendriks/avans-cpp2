#ifndef logging_h
#define logging_h

#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <ctime>

namespace machiavelli
{
    enum log_level
    {
        DBG,
        INFO,
        WARN,
        ERROR
    };
    
    class log
    {
        static std::mutex s_mutex;
        static const log_level s_level;
        static const bool s_print_level;
        static const bool s_print_time;
        
        inline std::string get_level_string(log_level level);
        
        bool m_open;
        log_level m_level;
    public:
        log();
        log(log_level level);
        ~log();
        
        template<typename T>
        log& operator<<(T obj)
        {
            if (m_level >= s_level) {
                std::cout << obj;
                m_open = true;
            }
            return *this;
        }
        
        bool is_open() const { return m_open; }
        log_level get_level() const { return m_level; }
    };
}

#endif
