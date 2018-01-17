#ifndef csv_document_h
#define csv_document_h

#include "csv_element.hpp"
#include "csv_record.hpp"

namespace machiavelli
{
    namespace csv
    {
        class document : public element<record, '\n'>
        {
        public:
            document() : element{} {}
            document(std::initializer_list<record> il) : element{il} {}
            
            void parse(std::istream& is) override;
        };
    }
}

#endif
