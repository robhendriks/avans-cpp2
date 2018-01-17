#ifndef character_card_factory_h
#define character_card_factory_h

#include <memory>
#include <map>
#include "character_card.hpp"

namespace machiavelli
{
    class character_card_factory
    {        
        std::map<int, std::shared_ptr<character_card>> m_characters;
    public:
        character_card_factory() : m_characters{} {}
        character_card_factory(const character_card_factory&) = delete;
        character_card_factory& operator=(const character_card_factory&) = delete;
        
        static character_card_factory& get_instance()
        {
            static character_card_factory instance;
            return instance;
        }
        
        bool character_exists(std::string name) const;
        
        character_card_factory& add(std::shared_ptr<character_card> character);
        std::shared_ptr<character_card> create(int id, const std::string& name, color c);
        
        std::vector<std::shared_ptr<character_card>> get_character_cards() const;
    };
}

#endif
