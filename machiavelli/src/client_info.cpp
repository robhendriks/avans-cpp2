#include "client_info.hpp"
#include "colors.hpp"

namespace machiavelli
{
    
    
    void client_info::show(const dialog& d) const
    {
        if (m_socket.is_open()) {
            m_socket << "\e[0G" << d.to_string() << "\e[0m" << PROMPT;
        }
    }
    
    void client_info::message(const std::string &msg) const
    {
        if (m_socket.is_open()) {
            m_socket << "\e[0G" << msg << "\e[0m\r\n" << PROMPT;
        }
    }
    
    void client_info::info(const std::string& msg, bool dim) const
    {
        message(colorize_info(msg, dim));
    }
    
    void client_info::warn(const std::string& msg, bool dim) const
    {
        message(colorize_warning(msg, dim));
    }
    
    void client_info::error(const std::string& msg, bool dim) const
    {
        message(colorize_error(msg, dim));
    }
    
    void client_info::clear() const
    {
        if (m_socket.is_open()) {
            m_socket << "\e[2J\e[0;0H" << PROMPT;
        }
    }
    
    void client_info::on_turn_begin()
    {
        m_player.on_turn_begin();
    }
    
    void client_info::on_turn_end()
    {
        m_player.on_turn_end();
    }
    
    std::string client_info::to_string() const
    {
        std::stringstream ss;
        ss << "\e[1m" << m_player.get_display_name() << "\e[0m\e[2m - " << get_socket().get_dotted_ip() << ':' << get_socket().get_port();
        return ss.str();
    }
}
