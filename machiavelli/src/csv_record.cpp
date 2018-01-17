#include "csv_record.hpp"

namespace machiavelli
{
    namespace csv
    {
        void record::parse(std::istream& is)
        {
            std::string value;
            while (std::getline(is, value, m_delimiter)) {
                emplace_back(value);
            }
            
            if (!is && value.empty()) {
                emplace_back("");
            }
        }
    }
}
