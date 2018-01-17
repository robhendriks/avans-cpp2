#ifndef card_deck_dialog_h
#define card_deck_dialog_h

#include "dialog.hpp"
#include "card_deck.hpp"

namespace machiavelli
{
    template<typename T>
    class card_deck_dialog : public dialog
    {
        const card_deck<T> m_deck;
    public:
        card_deck_dialog(const card_deck<T>& deck) : dialog{}, m_deck{deck} {}
        
        void format(std::stringstream& ss) const
        {
            dialog::format(ss);
            format_cards(ss);
        }
        
        void format_cards(std::stringstream& ss) const
        {
            if (m_deck.empty()) {
                ss << "\e[2mNo items" << ESCAPE;
                return;
            }
            
            size_t i = 0;
            for (auto card : m_deck) {
                if (!card) { continue; }
                ss << "\e[2m[" << i << "] \e[0m";
                format_card(ss, *card, i);
                ++i;
            }
        }
        
        void format_card(std::stringstream& ss, const T& card, size_t index) const;
    };
}

#endif
