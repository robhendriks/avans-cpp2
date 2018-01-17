#include "character_card_factory.hpp"

namespace machiavelli
{
    character_card_factory& character_card_factory::add(std::shared_ptr<character_card> character)
    {
        m_characters.emplace(character->get_id(), character);
        return *this;
    }
    
    std::shared_ptr<character_card> character_card_factory::create(int id, const std::string& name, color c)
    {
        auto it = m_characters.find(id);
        if (it == m_characters.end()) {
            throw std::runtime_error{"invalid character card ID '" + std::to_string(id) + '\''};
        }
        
        auto card = it->second;
        card->set_name(name);
        card->set_color(c);
        
        return std::dynamic_pointer_cast<character_card>(card);
    }
    
    bool character_card_factory::character_exists(std::string name) const
    {
        string_utils::to_lower_case(name);
        auto it = std::find_if(m_characters.begin(), m_characters.end(), [name](const auto& pair) {
            return name == string_utils::to_lower_case_copy(pair.second->get_name());
        });
        return it != m_characters.end();
    }
    
    std::vector<std::shared_ptr<character_card>> character_card_factory::get_character_cards() const
    {
        std::vector<std::shared_ptr<character_card>> result;
        std::transform(m_characters.begin(), m_characters.end(), std::back_inserter(result), [](auto& pair) {
            return pair.second;
        });
        return result;
    }
}
