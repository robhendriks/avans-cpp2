#include "networking/logging.h"

namespace machiavelli
{
    std::mutex log::s_mutex;
    
    const log_level log::s_level = DBG;
    const bool log::s_print_level = true;
    const bool log::s_print_time = true;
    
    inline std::string log::get_level_string(log_level level)
    {
        switch (level) {
            case DBG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARN:
                return "WARN";
            case ERROR:
                return "ERROR";
        }
    }
    
    log::log() : log{INFO} {}
    
    log::log(log_level level) : m_open{false}, m_level{level}
    {
        s_mutex.lock();
        
        std::stringstream ss;
        
        if (s_print_time) {
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            ss << std::put_time(std::localtime(&now_c), "%T") << ' ';
        }
        if (s_print_level) {
            ss << '[' << get_level_string(m_level) << "] ";
        }
            
        operator<<(ss.str());
    }
    
    log::~log()
    {        
        if (m_open) {
            std::cout << std::endl;
        }
        m_open = false;
        s_mutex.unlock();
    }
}
