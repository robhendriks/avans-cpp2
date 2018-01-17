#include "character_iterator.hpp"
#include "game.hpp"

namespace machiavelli
{
    void character_iterator::init()
    {
        auto& ccf = character_card_factory::get_instance();
        m_characters = ccf.get_character_cards();
        
        if (m_characters.empty()) {
            throw std::runtime_error{"this should not happen"};
        }
        
        std::sort(m_characters.begin(), m_characters.end(), [](auto a, auto b) {
            return a->get_id() < b->get_id();
        });
        
        reset();
    }
    
    void character_iterator::reset()
    {
        m_first = true;
        m_current = m_characters.begin();
    }
    
    bool character_iterator::advance()
    {
        if (m_first) {
            m_first = false;
            return true;
        } else if (m_current == m_characters.end()) {
            return false;
        }
        
        std::advance(m_current, 1);
        
        if (m_current == m_characters.end()) {
            return false;
        }
        return true;
    }
    
    std::shared_ptr<client_info> character_iterator::get_current_player()
    {
        std::lock_guard<std::mutex> lock{m_game.get_mutex()};
        
        auto& clients =  m_game.get_clients();
        
        auto it = std::find_if(clients.begin(), clients.end(), [this](std::shared_ptr<client_info> client) {
            return client->get_player().get_characters().has(get_current_character()->get_id());
        });
        if (it == clients.end()) {
            return nullptr;
        }
        return *it;
    }
    
    std::shared_ptr<character_card> character_iterator::get_current_character()
    {
        if (m_current == m_characters.end()) {
            throw std::runtime_error{"verzin iets zo "};
        }
        return *m_current;
    }
}
