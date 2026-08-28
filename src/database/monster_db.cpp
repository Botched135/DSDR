#include "DSDR/database/monster_db.hpp"
#include "DSDR/data/monster_data.hpp"
#include "DSDR/ds_enum_converters.hpp"
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

        if (toml::array* monsters = mdb_table["monsters"].as_array())
        {
            try
            {
                monsters->for_each([](auto&& entry)
                {
                    auto& tableEntry = *entry.as_table();
                    // each of them are tables
                    std::string_view name = tableEntry["name"].value<std::string_view>().value();
                    Creature::Organization org = ConverStrToEnum<Creature::Organization>(tableEntry["creature_org"].value<std::string_view>().value());
                    //Creature::Role role = 
                    u16 encounter_value = tableEntry["encounter_value"].value<u16>().value(); // No defaults
                    i16 death = tableEntry["death"].value_or(0);

                });
            }
            catch(std::bad_optional_access& ex)
            {
                // clear map
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