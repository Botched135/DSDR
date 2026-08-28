#include "DSDR/database/monster_db.hpp"
#include <fmt/core.h>
#include <toml++/toml.hpp>
#include <iostream>

namespace DSDR
{
    constexpr const char* s_toml_ext =".toml";

    i32 load_monster_from_file(const std::filesystem::path& in_file_path)
    {
        if(in_file_path.extension() != s_toml_ext)
        {
            return 0;
        }
        
        toml::table mdb_table;
        try
        {
            mdb_table = toml::parse_file(in_file_path.string());
           //std::cout<< mdb_table << std::endl;
        }
        catch (const toml::parse_error& err)
        {
            std::cout << err << std::endl;
            //fmt::print("Parsing failed: {}\n", err);
            return -1;
        }

        return 1;
       
    }
}