#ifndef character_iterator_h
#define character_iterator_h

#include "character_card_factory.hpp"

namespace machiavelli
{
    class game;
    class client_info;
    class character_iterator
    {
        using character_list = std::vector<std::shared_ptr<character_card>>;
        
        game& m_game;
        character_list m_characters;
        character_list::iterator m_current;
        bool m_first;
        
        void init();
    public:
        character_iterator(game& g) : m_game{g}, m_first{true} { init(); }
       
        void reset();
        bool advance();
        
        std::shared_ptr<client_info> get_current_player();
        std::shared_ptr<character_card> get_current_character();
    };
}

#endif
