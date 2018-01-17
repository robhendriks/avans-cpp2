#ifndef player_h
#define player_h

#include <string>
#include "wallet.hpp"
#include "card_manager.hpp"
#include "stats.hpp"

namespace machiavelli
{
    class player
    {
        std::string m_name;
        bool m_king;
        bool m_new_king;
        bool m_turn_over;
        int m_turn_count;
        bool m_has_accepted;
        bool m_has_rejected;
        bool m_has_picked;
        int m_build_count;
        bool m_first_eight;
        
        wallet m_wallet;
        card_deck<character_card> m_characters;
        card_deck<building_card> m_buildings;
        card_deck<building_card> m_built_buildings;
        card_deck<building_card> m_build_options;
    public:
        player(const std::string& name) : m_name{name}, m_king{false}, m_new_king{false}, m_turn_over{true}, m_turn_count{0}, m_has_accepted{false}, m_has_rejected{false}, m_has_picked{false}, m_build_count{0}, m_first_eight{false} {}
        
        void reset();
        void reset_turn();
        void reset_round();
        void on_turn_begin();
        void on_turn_end();
        
        int get_building_count() const;
        int get_building_score() const;
        bool has_all_building_colors() const;
        stats get_stats() const;
        
        std::string get_name() const { return m_name; }
        std::string get_display_name() const;
        void set_name(const std::string& name) { m_name = name; }
        bool is_king() const { return m_king; }
        void set_king(bool king) { m_king = king; }
        bool is_new_king() const { return m_new_king; }
        void set_new_king(bool new_king) { m_new_king = new_king; }
        bool is_turn_over() const { return m_turn_over; }
        void set_turn_over(bool turn_over) { m_turn_over = turn_over; }
        int get_turn_count() const { return m_turn_count; }
        void set_turn_count(int turn_count) { m_turn_count = turn_count; }
        
        bool has_accepted() const { return m_has_accepted; }
        void set_accepted(bool accepted) { m_has_accepted = accepted; }
        bool has_rejected() const { return m_has_rejected; }
        void set_rejected(bool rejected) { m_has_rejected = rejected; }
        
        bool has_picked() const { return m_has_picked; }
        void set_picked(bool picked) { m_has_picked = picked; }
        int get_build_count() const { return m_build_count; }
        void set_build_count(int build_count) { m_build_count = build_count; }
        bool is_first_eight() const { return m_first_eight; }
        void set_first_eight(bool first_eight) { m_first_eight = first_eight; }
        
        wallet& get_wallet() { return m_wallet; }
        const wallet& get_wallet() const { return m_wallet; }
        card_deck<character_card>& get_characters() { return m_characters; }
        const card_deck<character_card>& get_characters() const { return m_characters; }
        card_deck<building_card>& get_buildings() { return m_buildings; }
        const card_deck<building_card>& get_buildings() const { return m_buildings; }
        card_deck<building_card>& get_built_buildings() { return m_built_buildings; }
        const card_deck<building_card>& get_built_buildings() const { return m_built_buildings; }
        
        card_deck<building_card>& get_build_options() { return m_build_options; }
        const card_deck<building_card>& get_build_options() const { return m_build_options; }
    };
    
    inline bool operator==(const player& lhs, const player& rhs)
    {
        return string_utils::to_lower_case_copy(lhs.get_name()) == string_utils::to_lower_case_copy(rhs.get_name());
    }
    
    inline bool operator!=(const player& lhs, const player& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif
