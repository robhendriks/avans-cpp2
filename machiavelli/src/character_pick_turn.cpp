#include "character_pick_turn.hpp"
#include "character_action_turn.hpp"
#include "turn_manager.hpp"
#include "game.hpp"
#include "command_builder.hpp"

namespace machiavelli
{
    character_pick_turn::character_pick_turn(turn_manager& context) : turn{context, "pick_character"} {}
    
    void character_pick_turn::register_commands()
    {
        register_command()
            .name("accept")
            .description("accept a character card")
            .usage("<card_index>")
            .callback([this](command_sender& sender, const command_args& args) {
                if (sender.get_player().is_turn_over()) {
                    throw std::runtime_error{"It's not your turn"};
                } else if (sender.get_player().has_accepted()) {
                    throw std::runtime_error{"You've already accepted a character"};
                } else if (args.size() < 1) {
                    return false;
                }
                
                int i = std::stoi(args[0]);
                
                auto& g = get_context().get_game();
                std::shared_ptr<character_card> c;
                
                try {
                    c = g.get_characters().pop_at(i);
                } catch (const std::out_of_range&) {
                    throw std::runtime_error{"Invalid choice"};
                }
                
                if (c->get_id() == 4) {
                    g.set_new_king(sender.shared_from_this());
                    log(DBG) << "New king has been chosen";
                }
                
                c->set_owner(sender.shared_from_this());
                sender.get_player().get_characters().push(c);
                sender.info("You accepted '" + c->to_string() + '\'');
                
                sender.get_player().set_accepted(true);
                
                if ((sender.get_player().has_accepted() && sender.get_player().has_rejected()) || (sender.get_player().is_king() && sender.get_player().get_turn_count() == 0 && sender.get_player().has_accepted())) {
                    sender.get_player().set_accepted(false);
                    sender.get_player().set_rejected(false);
                    
                    g.advance_player();
                }

                if (g.get_characters().empty()) {
                    get_context().next<character_action_turn>();
                } else {
                    get_context().next<character_pick_turn>();
                }
                
                return true;
            });

        register_command()
            .name("reject")
            .description("reject a character card")
            .usage("<card_index>")
            .callback([this](command_sender& sender, const command_args& args) {
                if (sender.get_player().is_king() && sender.get_player().get_turn_count() == 0) {
                    throw std::runtime_error{"Thee cannot rejecteth any cards during this turneth"};
                } if (sender.get_player().is_turn_over()) {
                    throw std::runtime_error{"It's not your turn"};
                } else if (sender.get_player().has_rejected()) {
                    throw std::runtime_error{"You've already rejected a character"};
                } else if (args.size() < 1) {
                    return false;
                }
                
                int i = std::stoi(args[0]);
                
                auto& g = get_context().get_game();
                std::shared_ptr<character_card> c;
                
                try {
                    c = g.get_characters().pop_at(i);
                } catch (const std::out_of_range&) {
                    throw std::runtime_error{"Invalid choice"};
                }
                
                sender.info("You rejected '" + c->to_string() + '\'');
                sender.get_player().set_rejected(true);
                
                if (sender.get_player().has_accepted() && sender.get_player().has_rejected()) {
                    sender.get_player().set_accepted(false);
                    sender.get_player().set_rejected(false);
                    
                    g.advance_player();
                }
                
                if (g.get_characters().empty()) {
                    get_context().next<character_action_turn>();
                } else {
                    get_context().next<character_pick_turn>();
                }
                
                return true;
            });
    }

    void character_pick_turn::on_enter()
    {
        turn::on_enter();
        
        auto& g = get_context().get_game();
        if (auto current_player = g.get_current_player()) {
            current_player->info("Use the 'accept' and 'reject' command to pick your cards.", true);
            current_player->show(g.get_characters());
        }
    }

    void character_pick_turn::on_leave()
    {
        turn::on_leave();
    }
}
