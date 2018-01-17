#include "character_card.hpp"
#include "client_info.hpp"

namespace machiavelli
{
    void character_card::use(game& g, command_sender& sender, const command_args& args)
    {
        if (m_used) {
            throw std::runtime_error{"You've already used this characters special ability"};
        }
        if (on_use(g, sender, args)) {
            m_used = true;
        }
    }
    
    void character_card::reset()
    {
        set_alive(true);
        set_used(false);
        set_robbed(false);
        set_owner(nullptr);
    }
    
    void character_card::kill()
    {
        log(INFO) << "Killed character '" << get_name() << '\'';
        set_alive(false);
    }
    
    void character_card::rob(command_sender& thief)
    {
        if (!m_owner) {
            throw std::runtime_error{"A character without owner cannot be robbed"};
        } else if (m_robbed) {
            throw std::runtime_error{"This character has already been robbed"};
        }
        
        log(INFO) << "Robbed character '" << get_name() << '\'';
        
        set_robbed(true);
        m_owner->get_player().get_wallet().transfer(thief.get_player().get_wallet());
    }
    
    void character_card::set_owner(std::shared_ptr<client_info> owner)
    {
        if (m_owner) {
            log(DBG) << "Character '" << get_name() << "' was previously owned by '" << m_owner->get_player().get_name() + '\'';
        }
        m_owner = owner;
        if (m_owner) {
            log(DBG) << "Character '" << get_name() << "' is currently owned by '" << m_owner->get_player().get_name() + '\'';
        }
    }
}
