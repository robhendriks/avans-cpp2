#ifndef csv_element_h
#define csv_element_h

#include <vector>
#include <istream>
#include <sstream>
#include "string_utils.hpp"

namespace machiavelli
{
    namespace csv
    {
        template<typename T, char D>
        class element : public string_utils::string_convertible, public std::vector<T>
        {
        protected:
            char m_delimiter = D;
        public:
            element() : std::vector<T>{}
            {
                static_assert(std::is_base_of<string_utils::string_convertible, T>::value, "T must be a derivative of string_convertible");
            }
            
            element(std::initializer_list<T> il) : std::vector<T>{il}
            {
            }
            
            virtual std::string to_string() const override
            {
                std::stringstream ss;
                
                for (auto it = this->begin(); it != this->end(); ++it) {
                    if (it != this->begin()) { ss << D; }
                    ss << it->to_string();
                }
                
                return ss.str();
            }
            
            virtual void parse(std::istream& is) = 0;
        };
        
        template<typename T, char D>
        inline std::istream& operator>>(std::istream& is, element<T, D>& e)
        {
            e.parse(is);
            return is;
        }
    }
}


#endif
