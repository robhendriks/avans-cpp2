#ifndef string_convertible_h
#define string_convertible_h

#include <string>
#include <ostream>

namespace machiavelli
{
    namespace string_utils
    {
        class string_convertible
        {
        public:
            virtual std::string to_string() const = 0;
            
            operator std::string() const
            {
                return to_string();
            }
        };
        
        inline std::ostream& operator<<(std::ostream& os, const string_convertible& sc)
        {
            os << sc.to_string();
            return os;
        }
    }
}

#endif
