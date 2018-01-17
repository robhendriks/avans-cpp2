#ifndef csv_record_h
#define csv_record_h

#include "csv_element.hpp"
#include "csv_field.hpp"

namespace machiavelli
{
    namespace csv
    {
        class record : public element<field, ';'>
        {
        public:
            record() : element{} {}
            record(std::initializer_list<field> il) : element{il} {}
            
            void parse(std::istream& is) override;
        };
    }
}

#endif
