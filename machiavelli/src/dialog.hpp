#ifndef dialog_hpp
#define dialog_hpp

#include <string>
#include <sstream>
#include "string_utils.hpp"

namespace machiavelli
{
    class dialog : public string_utils::string_convertible
    {
        std::string m_title;
        std::string m_body;
    protected:
        static const char* ESCAPE;
        
        virtual void format(std::stringstream& ss) const;
        
    public:
        dialog() : dialog{"", ""} {}
        dialog(const std::string& title) : dialog{title, ""} {}
        dialog(const std::string& title, const std::string& body) : m_title{title}, m_body{body} {}
        
        std::string to_string() const;
        
        std::string get_title() const { return m_title; }
        void set_title(const std::string& title) { m_title = title; }
        std::string get_body() const { return m_body; }
        void set_body(const std::string& body) { m_body = body; }
    };
}

#endif
