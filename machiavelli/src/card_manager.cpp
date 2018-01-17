#include <networking/logging.h>

#include "card_manager.hpp"
#include "character_card_factory.hpp"
#include "character_card.hpp"

namespace machiavelli
{
    void card_manager::load_file(const std::string& file_name)
    {
        std::ifstream is{file_name, std::ifstream::in};
        
        if (!is.is_open()) {
            throw std::runtime_error{"could not open file '" + file_name + '\''};
        }
        
        csv::document doc;
        is >> doc;
        
        for (auto& record : doc) {
            try {
                if (record.size() >= 4) {
                    load_building(record);
                } else if (record.size() == 3) {
                    load_character(record);
                }
            } catch (const std::exception& e) {
                log(ERROR) << e.what();
            }
        }
    }
    
    void card_manager::load_character(const csv::record& record)
    {
        m_characters.push(character_card_factory::get_instance()
                          .create(record[0].get<int>(),
                                  record[1].get<std::string>(),
                                  record[2].get<color>()));
    }
    
    void card_manager::load_building(const csv::record& record)
    {
        m_buildings.push(std::make_shared<building_card>(record[0].get<std::string>(),
                                                         record[1].get<int>(),
                                                         record[2].get<color>(),
                                                         record[3].get<std::string>()));
    }
    
    void card_manager::load()
    {
        m_characters.clear();
        m_buildings.clear();
        
        load_file("data/characters.csv");
        load_file("data/buildings.csv");
    }
}
