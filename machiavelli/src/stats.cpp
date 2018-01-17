#include "stats.hpp"
#include "player.hpp"

namespace machiavelli
{
    void stats::init()
    {
        m_income = m_player.get_wallet().get_income();
        m_expenses = m_player.get_wallet().get_expenses();
        m_building_count = m_player.get_building_count();
        m_building_score = m_player.get_building_score();
        m_bonus_colors = m_player.has_all_building_colors();
        m_bonus_first_eight = m_player.is_first_eight();
        m_bonus_eight = m_building_count >= 8;
        
        if (m_bonus_first_eight) {
            m_bonus_score += 4;
        } else if (m_bonus_eight) {
            m_bonus_score += 2;
        }
        
        if (m_bonus_colors) {
            m_bonus_score += 3;
        }
    }
    
    std::string stats::to_string() const
    {
        std::stringstream ss;
        ss  << "\e[2m──────────────────────────────────────────────────\e[0m\r\n"
            << "Income:\t\t\t" << m_income << " gold\r\n"
            << "Expenses:\t\t" << m_expenses << " gold\r\n"
            << "\e[2m──────────────────────────────────────────────────\e[0m\r\n"
            << "Building count:\t\t" << m_building_count << "\r\n"
            << "Building score:\t\t" << m_building_score << "\r\n"
            << "\e[2m──────────────────────────────────────────────────\e[0m\r\n"
            << "Color bonus:\t\t" << (m_bonus_colors ? "\e[32myes" : "\e[31mno") << "\e[0m\r\n"
            << "First city bonus:\t" << (m_bonus_first_eight ? "\e[32myes" : "\e[31mno") << "\e[0m\r\n"
            << "City bonus:\t\t" << (m_bonus_eight ? "\e[32myes" : "\e[31mno") << "\e[0m\r\n"
            << "\e[2m──────────────────────────────────────────────────\e[0m\r\n"
            << "Score:\t\t\t" << m_building_score << "\r\n"
            << "Bonus score:\t\t" << m_bonus_score << "\r\n"
            << "\r\nTotal score:\t\t" << get_total_score() << "\r\n"
            << "\e[2m──────────────────────────────────────────────────\e[0m";
        
        return ss.str();
    }
}
