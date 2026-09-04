#pragma once

#include <filesystem>
#include "DSDR/utility/type_defs.hpp"

namespace DSDR
{
    // Should probably have a DB for Malice actions

    i32 load_monster_from_toml(const std::filesystem::path& in_file_path);

    i32 load_monster_from_json(const std::filesystem::path& in_file_path);

}