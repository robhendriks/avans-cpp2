#ifndef building_card_h
#define building_card_h

#include "card.hpp"
#include "color.hpp"

namespace machiavelli
{
    class building_card : public card
    {
        int m_cost;
        color m_color;
        std::string m_description;
    public:
        building_card(const std::string& name, int cost, color col, const std::string& description) : card{name}, m_cost{cost}, m_color{col}, m_description{description} {}
        
        std::shared_ptr<card> clone() const override;
        
        int get_cost() const { return m_cost; }
        int get_destroy_cost() const { return m_cost == 1 ? 0 : m_cost + 1; }
        color get_color() const { return m_color; }
        std::string get_description() const { return m_description; }
    };
}

#endif
