#ifndef stats_h
#define stats_h

#include <sstream>
#include "string_utils.hpp"

namespace machiavelli
{
    class player;
    class stats : public string_utils::string_convertible
    {
        const player& m_player;
        int m_income;
        int m_expenses;
        int m_building_count;
        int m_building_score;
        bool m_bonus_colors;
        bool m_bonus_first_eight;
        bool m_bonus_eight;
        int m_bonus_score;
        
        void init();
        
    public:
        stats(const player& p) : m_player{p}, m_income{0}, m_expenses{0}, m_building_count{0}, m_building_score{0}, m_bonus_colors{false}, m_bonus_first_eight{false}, m_bonus_eight{false}, m_bonus_score{0} { init(); }
        
        const player& get_player() const { return m_player; }
        int get_income() const { return m_income; }
        int get_expenses() const { return m_expenses; }
        int get_building_count() const { return m_building_count; }
        int get_building_score() const { return m_building_score; }
        int get_total_score() const { return m_building_score + m_bonus_score; }
        
        std::string to_string() const override;
    };
}

#endif
