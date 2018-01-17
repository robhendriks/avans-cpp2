#include "card_deck.hpp"
#include "character_card.hpp"
#include "building_card.hpp"

namespace machiavelli
{
    template<>
    int card_deck<character_card>::max_build_count() const
    {
        auto it = std::max_element(m_cards.begin(), m_cards.end(), [](auto a, auto b) {
            return a->max_build_count() < b->max_build_count();
        });
        if (it == m_cards.end()) {
            throw std::runtime_error{"this should not happen either"};
        }
        return (*it)->max_build_count();
    }
    
    template<>
    int card_deck<building_card>::count_color(color c) const
    {
        return std::accumulate(m_cards.begin(), m_cards.end(), 0, [c](int a, std::shared_ptr<building_card> b) {
            return (b->get_color() == c) ? a + 1 : a;
        });
    }
    
    template<>
    std::map<color, int> card_deck<building_card>::count_colors() const
    {
        std::map<color, int> result;
        for_each_color([this, &result](color c) {
            result.emplace(c, count_color(c));
        });
        return result;
    }
    
    template<>
    bool card_deck<building_card>::has_all_colors() const
    {
        return check_each_color([this](color c) {
            if (count_color(c) == 0) {
                return false;
            }
            return true;
        });
    }
}
