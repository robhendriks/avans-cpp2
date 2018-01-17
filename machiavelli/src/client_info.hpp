#ifndef client_info_h
#define client_info_h

#include <string>
#include <utility>

#include <networking/Socket.h>
#include "player.hpp"
#include "dialog.hpp"
#include "card_deck_dialog.hpp"
#include "string_utils.hpp"

namespace machiavelli
{
    static const char* PROMPT = "\e[0m\e[2m~> \e[0m";
    
    class client_info : public string_utils::string_convertible, public std::enable_shared_from_this<client_info>
    {
        static const std::string COLOR_INFO;
        static const std::string COLOR_WARNING;
        static const std::string COLOR_ERROR;
        
        bool m_quit;
        bool m_silent;
        Socket m_socket;
        player m_player;
    public:
        client_info(Socket socket, player player) : m_quit{false}, m_silent{false}, m_socket{std::move(socket)}, m_player{std::move(player)} {}
        
        void show(const dialog& d) const;
        
        template<typename T>
        void show(const card_deck<T>& deck) const
        {
            card_deck_dialog<T> d{deck};
            show(d);
        }
        
        void message(const std::string& msg) const;
        void info(const std::string& msg, bool dim = false) const;
        void warn(const std::string& msg, bool dim = false) const;
        void error(const std::string& msg, bool dim = false) const;
        
        void clear() const;
        
        void on_turn_begin();
        void on_turn_end();
        
        void quit() { m_quit = true; }
        bool should_quit() const { return m_quit; }
        bool is_silent() const { return m_silent; }
        void set_silent(bool silent) { m_silent = silent; }
        
        Socket& get_socket() { return m_socket; }
        const Socket& get_socket() const { return m_socket; }
        player& get_player() { return m_player; }
        const player& get_player() const { return m_player; }
        
        std::string to_string() const override;
    };
}

#endif
