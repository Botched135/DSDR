#include <filesystem>
#include <fstream>

namespace DSDR
{
    // Should probably have a DB for Malice actions
    constexpr std::string toml_ext =".toml";
    void LoadMDBFromFile(const std::filesystem::path& in_file_path)
    {
        if(in_file_path.extension() != toml_ext)
        {
            // Write good error message
            return;
        }
        std::ifstream monster_db_file(in_file_path);
        if(!monster_db_file.open())
        {
            // something is wrong with the file 
            return;
        }

    }

}