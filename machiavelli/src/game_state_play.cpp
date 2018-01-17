#include "game_state_play.hpp"
#include "game_state_lobby.hpp"
#include "game_state_manager.hpp"
#include "game.hpp"
#include "command_builder.hpp"
#include "character_setup_turn.hpp"

namespace machiavelli
{
    game_state_play::game_state_play(game_state_manager& context) : game_state{context, "play"}, m_turn_manager{context.get_game(), *this}, m_character_iterator{context.get_game()}
    {
    }
    
    void game_state_play::register_commands()
    {
        register_command()
            .name("cheat")
            .description("cheating")
            .usage("[args...]")
            .visible(false)
            .callback([this](command_sender& sender, const command_args& args) {
                auto& g = get_context().get_game();
                if (g.get_vars().is_false("sv_cheats")) {
                    throw std::runtime_error{"server has cheats disabled by default"};
                } else if (args.size() < 1) {
                    return false;
                }
                
                if (args[0] == "gold") {
                    if (args.size() < 3) { return false; }
                    
                    if (args[1] == "add") {
                        sender.get_player().get_wallet().add(std::stoi(args[2]));
                    } else if (args[1] == "remove") {
                        sender.get_player().get_wallet().remove(std::stoi(args[2]));
                    } else {
                        throw std::invalid_argument{"expected either 'add' or 'remove'"};
                    }
                } else {
                    return false;
                }
                
                g.warn("Player '" + sender.get_player().get_display_name() + "' used cheat '" + string_utils::join(args, ' ') + '\'', true);
                return true;
            });
    }

    void game_state_play::on_enter()
    {
        game_state::on_enter();
        m_turn_manager.next<character_setup_turn>();
        m_character_iterator.reset();
    }
    
    void game_state_play::on_leave()
    {
        game_state::on_leave();
        m_turn_manager.set_turn(nullptr); // cleanup, sort of...
    }
    
    void game_state_play::on_client_leave(command_sender &client)
    {
        get_context().next<game_state_lobby>();
    }
}
