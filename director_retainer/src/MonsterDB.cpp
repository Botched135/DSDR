#include "MonsterDB.hpp"

#include <toml++/toml.hpp>
#include <iostream>
#include <SDL3/SDL_log.h>

namespace DSDR
{
    constexpr const char* s_toml_ext =".toml";


    std::optional<int> LoadMDBFromFile(const std::filesystem::path& in_file_path)
    {

        SDL_Log("%ls\n", in_file_path.c_str());
        if(in_file_path.extension() != s_toml_ext)
        {
            SDL_Log("Extension fail\n");
            return std::nullopt;
        }
         toml::table mdb_table;
        try
        {
            SDL_Log("Here?");
            mdb_table = toml::parse_file(in_file_path.string());
            SDL_Log("Here!");
            std::cout<<mdb_table << std::endl;
        }
        catch (const toml::parse_error& err)
        {
            SDL_Log("Parsing failed:%s\n", err.what());
            return std::nullopt;
        }

        return 1;
       
    }
}