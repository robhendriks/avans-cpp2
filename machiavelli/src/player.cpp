#include "player.hpp"

namespace machiavelli
{
    void player::reset()
    {
        m_king = false;
        m_new_king = false;
        m_turn_over = true;
        m_turn_count = 0;
        m_has_accepted = false;
        m_has_rejected = false;
        m_has_picked = false;
        m_build_count = 0;
        m_wallet.reset();
        m_characters.clear();
        m_buildings.clear();
        m_built_buildings.clear();
        m_first_eight = false;
    }
    
    void player::reset_turn()
    {
        m_has_picked = false;
        m_build_count = 0;
    }
    
    void player::reset_round()
    {
        m_characters.clear();
        m_turn_count = 0;
        
        reset_turn();
    }
    
    void player::on_turn_begin()
    {
        set_turn_over(false);
    }
    
    void player::on_turn_end()
    {
        set_turn_over(true);
        ++m_turn_count;
    }
    
    int player::get_building_count() const
    {
        return m_built_buildings.size();
    }
    
    int player::get_building_score() const
    {
        return std::accumulate(m_built_buildings.begin(), m_built_buildings.end(), 0, [](int a, auto b) {
            return a + b->get_cost();
        });
    }
    
    bool player::has_all_building_colors() const
    {
        return m_built_buildings.has_all_colors();
    }
    
    stats player::get_stats() const
    {
        return stats{*this};
    }
    
    std::string player::get_display_name() const
    {
        if (is_king()) {
            return m_name + " \u265A ";
        }
        return m_name;
    }
}
