#include "building_card.hpp"

namespace machiavelli
{
    std::shared_ptr<card> building_card::clone() const
    {
        return std::make_shared<building_card>(get_name(), m_cost, m_color, m_description);
    }
}
