#ifndef character_card_h
#define character_card_h

#include <stdexcept>
#include "card.hpp"
#include "command.hpp"
#include <iostream>
#include "color.hpp"

namespace machiavelli
{
    class game;
    class character_card_error : public std::runtime_error
    {
    public:
        character_card_error() : std::runtime_error{""} {}
    };
    
    class character_card : public card
    {
        color m_color;
        int m_id;
        bool m_alive;
        bool m_used;
        bool m_robbed;
        std::shared_ptr<client_info> m_owner;
    protected:
        void set_alive(bool alive) { m_alive = alive; }
        void set_used(bool used) { m_used = used; }
        void set_robbed(bool robbed) { m_robbed = robbed; }
        
        virtual bool on_use(game& g, command_sender& sender, const command_args& args) = 0;
    public:
        character_card(const std::string& name, color c, int id) : m_color{c}, m_alive{true}, m_used{false}, m_robbed{false}, m_owner{nullptr}, card{name}, m_id{id} {}
        
        character_card(const character_card&) = delete;
        character_card& operator=(const character_card&) = delete;
            
        virtual void use(game& g, command_sender& sender, const command_args& args);
        
        virtual int max_build_count() const { return 1; }
        
        std::shared_ptr<card> clone() const
        {
            throw std::runtime_error{"not implemented"};
        }
        
        void kill();
        void rob(command_sender& thief);
        void reset();
        
        color get_color() const { return m_color; }
        void set_color(color c) { m_color = c; }
        int get_id() const { return m_id; }
        bool is_alive() const { return m_alive; }
        bool is_used() const { return m_used; }
        bool is_robbed() const { return m_robbed; }
        virtual bool can_destroy() const { return true; }
        
        std::shared_ptr<client_info> get_owner() const { return m_owner; }
        void set_owner(std::shared_ptr<client_info> owner);
    };
}

#endif
