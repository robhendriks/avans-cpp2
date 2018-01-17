#ifndef client_command_h
#define client_command_h

#include <string>
#include <memory>

namespace machiavelli
{
    class client_info;
    class client_command
    {
        std::string m_text;
        std::weak_ptr<client_info> m_client;
    public:
        client_command(const std::string& text, std::weak_ptr<client_info> client) : m_text{text}, m_client{client} {}
        
        std::string get_text() const { return m_text; }
        std::weak_ptr<client_info> get_client() const { return m_client; }
    };
}

#endif
