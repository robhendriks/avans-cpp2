#include "character_card_factory.hpp"
#include "characters.hpp"
#include "server.hpp"

#include "character_iterator.hpp"

int main(int argc, const char * argv[])
{
    character_card_factory::get_instance()
        .add(std::make_shared<moordenaar>())
        .add(std::make_shared<dief>())
        .add(std::make_shared<magier>())
        .add(std::make_shared<koning>())
        .add(std::make_shared<prediker>())
        .add(std::make_shared<koopman>())
        .add(std::make_shared<bouwmeester>())
        .add(std::make_shared<condottiere>());

    options default_vars {
        {"sv_cheats", 0},
        {"sv_ignore_build_limits", 0}
    };
    
    server s {default_vars};
    s.start();
    
    return 0;
}
