#include "DSDR/database/monster_db.hpp"
#include "DSDR/data/monster_data.hpp"
#include "DSDR/ds_enum_converters.hpp"
#include "DSDR/toml_helpers.hpp"
#include <fmt/core.h>
#include <toml++/toml.hpp>
#include <iostream>
#include <string_view>

namespace DSDR
{
    constexpr const char* s_toml_ext =".toml";

    i32 load_monster_from_file(const std::filesystem::path& in_file_path)
    {
        if(in_file_path.extension() != s_toml_ext) return 0;
        
        toml::table mdb_table;
        try
        {
            mdb_table = toml::parse_file(in_file_path.string());
        }
        catch (const toml::parse_error& err)
        {
            std::cerr<<"Error parsing file \"" << *err.source().path << "\":\n" << err.description() << "\n" << err.source().begin << std::endl;

            return -1;
        }

        initialize_enum_maps();

        if (toml::array* monsters = mdb_table["monsters"].as_array())
        {
            try
            {
                monsters->for_each([](auto&& entry)
                {
                    // TODO: the exception that is thrown needs to be useful
                    auto& tableEntry = *entry.as_table();
                    // each of them are tables
                    std::string_view name = extract_val<std::string_view>(tableEntry["name"]);
                    Creature::Organization org = convert_str_to_enum<Creature::Organization>(extract_str(tableEntry["creature_org"]));
                    Creature::Role role = convert_str_to_enum<Creature::Role>(extract_str(tableEntry["creature_role"]));
                    u16 encounter_value = extract_val<u16>(tableEntry["encounter_value"]); // No defaults
                    i16 death = tableEntry["death"].value_or(0);
                    u32 types = extract_flags<Creature::KeywordFlags>(tableEntry["types"]);
                    u16 level = extract_val<u16>(tableEntry["level"]);
                    Size size = {};
                    u16 speed = extract_val<u16>(tableEntry["speed"]);
                    u16 stamina = extract_val<u16>(tableEntry["stamina"]);
                    u16 stability = extract_val<u16>(tableEntry["stability"]);
                    u16 free_strike = extract_val<u16>(tableEntry["free_strike"]);

                    // imunity
                    // weakness
                    
                    u16 movement = extract_flags<Creature::MovementFlags>(tableEntry["movement"]);
                    
                    Characteristics characteristics = {};

                    u16 turns_per_round = tableEntry["turns_per_round"].value_or(1);
                    u16 triggers_per_round = tableEntry["triggers_per_round"].value_or(1);
                    EndEffect end_effect = {};

                    // Abilities
                    // Villian_actions
                    // malice_actions
                    // traits 
                    // Captain bonus

                    fmt::print("Done with {}\n", name);
                    

                    

                });
            }
            catch(std::bad_optional_access& ex)
            {
                fmt::print("{}\n", ex.what());
                return -1;
            }
        }   
        
        return 1;
       
    }

    MonsterEntry generate_monster_entry()
    {
        return {};
    }
}