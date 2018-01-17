#include "csv_field.hpp"

namespace machiavelli
{
    namespace csv
    {
        std::string field::to_string() const
        {
            return m_value;
        }
    }
}
