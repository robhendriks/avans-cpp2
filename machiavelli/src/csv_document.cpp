#include "csv_document.hpp"

namespace machiavelli
{
    namespace csv
    {
        void document::parse(std::istream& is)
        {
            std::string line;
            
            while (std::getline(is, line)) {
                string_utils::clean(line);
                
                if (line.empty()) { continue; }
                
                std::stringstream ss{line};
                record r;
                ss >> r;
                push_back(r);
            }
        }
    }
}
