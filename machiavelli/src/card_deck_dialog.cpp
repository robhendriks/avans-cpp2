#include "card_deck_dialog.hpp"
#include "character_card.hpp"
#include "building_card.hpp"

namespace machiavelli
{
    template<>
    void card_deck_dialog<character_card>::format_card(std::stringstream& ss, const character_card& card, size_t index) const
    {
        ss << card.get_name();
        if (card.get_color() != NONE) {
            ss << ' ' << ansi_code_from_color(card.get_color()) << "\u265C\e[0m";
        }
        ss << ESCAPE;
    }
    
    template<>
    void card_deck_dialog<building_card>::format_card(std::stringstream& ss, const building_card& card, size_t index) const
    {
        ss << ansi_code_from_color(card.get_color()) << "\u265C  \e[0m"
        << card.get_name()
        << " \e[2m- \e[0m"
        << "\e[38;5;214m$" << card.get_cost() << "\e[0m"
        << " \e[38;5;94m($" << card.get_destroy_cost() << ")\e[0m"
        << ESCAPE;
    }
}
