#ifndef card_h
#define card_h

#include <networking/logging.h>
#include "string_utils.hpp"

namespace machiavelli
{
    class card : public string_utils::string_convertible
    {
        std::string m_name;
    public:
        card(const std::string& name) : m_name{name} { }
        
        virtual std::shared_ptr<card> clone() const = 0;
        
        std::string to_string() const override;
        
        std::string get_name() const { return m_name; }
        void set_name(const std::string& name) { m_name = name; }
    };
}

#endif
