#include "dialog.hpp"

namespace machiavelli
{
    const char* dialog::ESCAPE = "\r\n";
    
    void dialog::format(std::stringstream& ss) const
    {
        if (!m_title.empty()) {
            ss << m_title << ESCAPE;
        }
        if (!m_body.empty()) {
            ss << m_body << ESCAPE;
        }
    }
    
    std::string dialog::to_string() const
    {
        std::stringstream ss;
        format(ss);
        return ss.str();
    }
}
