#include "DSDR/database/monster_db.hpp"
#include "DSDR/data/monster_data.hpp"
#include <fmt/core.h>
#include <toml++/toml.hpp>
#include <iostream>

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
            monsters->for_each([](auto&& entry)
            {
                auto& tableEntry = *entry.as_table();
                // each of them are tables
                std::string name = tableEntry["name"].value_or("");
            });
        }   
        
        return 1;
       
    }

    MonsterEntry generate_monster_entry()
    {
        return {};
    }
}