#ifndef card_deck_h
#define card_deck_h

#include <deque>
#include <map>
#include <memory>
#include <networking/logging.h>
#include "string_utils.hpp"
#include "card.hpp"
#include "color.hpp"
#include "vector_utils.hpp"

namespace machiavelli
{
    template<class T>
    class card_deck : public string_utils::string_convertible
    {
        using card_list = std::deque<std::shared_ptr<T>>;
        
        card_list m_cards;
    public:
        card_deck()
        {
            static_assert(std::is_base_of<card, T>::value, "T must be a derivative of card");
        }
        
        ~card_deck()
        {
        }
        
        void swap(card_deck<T>& other)
        {
            m_cards.swap(other.m_cards);
        }
        
        void transfer(card_deck<T>& other)
        {
            while (!empty()) {
                other.push(pop());
            }
        }
        
        void transfer_back(card_deck<T>& other)
        {
            while (!empty()) {
                other.push_back(pop());
            }
        }
        
        void push(std::shared_ptr<T> card)
        {
            if (card) {
                m_cards.push_front(card);
            }
        }
        
        void push_back(std::shared_ptr<T> card)
        {
            if (card) {
                m_cards.push_back(card);
            }
        }
        
        std::shared_ptr<T> find(std::string name)
        {
            string_utils::to_lower_case(name);
            auto it = std::find_if(m_cards.begin(), m_cards.end(), [name](auto card) {
                return string_utils::to_lower_case_copy(card->get_name()) == name;
            });
            if (it == m_cards.end()) {
                return nullptr;
            }
            return *it;
        }
        
        template<class C>
        decltype(auto) find() const
        {
            static_assert(std::is_base_of<card, C>::value, "C must be a derivative of card");
            
            return std::find_if(m_cards.begin(), m_cards.end(), [](auto c) {
                if (std::dynamic_pointer_cast<C>(c) != nullptr) {
                    return true;
                }
                return false;
            });
        }
        
        template<class C>
        bool has() const
        {
            return find<C>() != m_cards.end();
        }
        
        bool has(int id) const
        {
            auto it = std::find_if(m_cards.begin(), m_cards.end(), [id](std::shared_ptr<T> card) {
                return card->get_id() == id;
            });
            return it != m_cards.end();
        }

        template<class C>
        std::shared_ptr<C> find_and_remove()
        {
            static_assert(std::is_base_of<card, C>::value, "C must be a derivative of card");
            
            auto it = find<C>();
            if (it == m_cards.end()) {
                throw std::runtime_error{"haha, yes"};
            }
            m_cards.erase(it);
            return std::dynamic_pointer_cast<C>(*it);
        }
        
        std::shared_ptr<T> pop()
        {
            if (empty()) {
                log(WARN) << "deck empty; nothing to pop";
                return nullptr;
            }
            auto card = m_cards.front();
            m_cards.pop_front();
            return card;
        }
        
        std::shared_ptr<T> pop_at(size_t i)
        {
            if (empty() || i < 0 || i > m_cards.size() - 1) {
                throw std::out_of_range{"index out of range '" + std::to_string(i) + '\''};
            }
            
            auto it = m_cards.begin();
            std::advance(it, i);
            
            auto card = *it;
            m_cards.erase(it);
            return card;
        }
        
        std::shared_ptr<T> pop_random()
        {
            if (empty()) {
                log(WARN) << "deck empty; nothing to pop";
                return nullptr;
            }
            auto it = vector_utils::find_random(m_cards.begin(), m_cards.end());
            auto card = *it;
            m_cards.erase(it);
            return card;
        }
        
        std::shared_ptr<T> peek() const
        {
            if (empty()) {
                log(WARN) << "deck empty; nothing to peek";
                return nullptr;
            }
            return m_cards.front();
        }

        std::shared_ptr<T> peek_at(size_t i) const
        {
            if (empty() || i < 0 || i > m_cards.size() - 1) {
                throw std::out_of_range{"index out of range '" + std::to_string(i) + '\''};
            }
            
            auto it = m_cards.begin();
            std::advance(it, i);
            return *it;
        }
        
        void clear()
        {
            m_cards.clear();
        }
        
        std::string to_string() const
        {
            std::stringstream ss;
            for (auto it = begin(); it != end(); ++it) {
                if (it != begin()) { ss << std::endl; }
                ss << (*(*it));
            }
            return ss.str();
        }
        
        void shuffle()
        {
            std::default_random_engine gen{unsigned(time(0))};
            std::shuffle(m_cards.begin(), m_cards.end(), gen);
        }
        
        void shuffle(int n)
        {
            for (int i = 0; i < n; ++i) {
                shuffle();
            }
        }
        
        bool empty() const { return m_cards.empty(); }
        
        decltype(auto) begin() { return m_cards.begin(); }
        decltype(auto) begin() const { return m_cards.begin(); }
        decltype(auto) end() { return m_cards.end(); }
        decltype(auto) end() const { return m_cards.end(); }
        decltype(auto) size() const { return m_cards.size(); }
        
        std::vector<std::string> get_card_names() const
        {
            std::vector<std::string> result;
            std::transform(m_cards.begin(), m_cards.end(), std::back_inserter(result), [](auto card) {
                return card->to_string();
            });
            return result;
        }
        
        int count_color(color c) const;
        std::map<color, int> count_colors() const;
        bool has_all_colors() const;
        
        int max_build_count() const;
    };
}

#endif
