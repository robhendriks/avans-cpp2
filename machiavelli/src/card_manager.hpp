#ifndef card_manager_h
#define card_manager_h

#include <fstream>
#include "character_card.hpp"
#include "building_card.hpp"
#include "card_deck.hpp"
#include "csv.hpp"

namespace machiavelli
{
    class card_manager
    {
        card_deck<character_card> m_characters;
        card_deck<building_card> m_buildings;
        
        void load_file(const std::string& file_name);
        void load_character(const csv::record& record);
        void load_building(const csv::record& record);
        
    public:
        card_manager() : m_characters{}, m_buildings{} {}
        
        card_deck<character_card>& get_characters() { return m_characters; }
        const card_deck<character_card>& get_characters() const { return m_characters; }
        card_deck<building_card>& get_buildings() { return m_buildings; }
        const card_deck<building_card>& get_buildings() const { return m_buildings; }
        
        void load();
    };
}

#endif
