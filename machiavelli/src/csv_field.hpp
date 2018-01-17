#ifndef csv_field_h
#define csv_field_h

#include "string_utils.hpp"
#include "color.hpp"

namespace machiavelli
{
    namespace csv
    {
        class field : public string_utils::string_convertible
        {
        protected:
            std::string m_value;
        public:
            field(const std::string& value) : m_value{value} {}
            
            template<typename T>
            T get() const
            {
            }
            
            std::string get_value() const { return m_value; }
            void set_value(const std::string& value) { m_value = value; }
            
            std::string to_string() const override;
        };
        
        template<>
        inline std::string field::get() const
        {
            return m_value;
        }
        
        template<>
        inline int field::get() const
        {
            return std::stoi(m_value);
        }
        
        template<>
        inline long field::get() const
        {
            return std::stol(m_value);
        }
        
        template<>
        inline float field::get() const
        {
            return std::stof(m_value);
        }
        
        template<>
        inline double field::get() const
        {
            return std::stod(m_value);
        }
        
        template<>
        inline color field::get() const
        {
            return color_from_string(m_value);
        }
    }
}

#endif
