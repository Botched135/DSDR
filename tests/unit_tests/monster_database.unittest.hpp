#pragma once

#include <doctest.h>
#include "DSDR/database/monster_db.hpp"
#include "DSDR/ds_enum_converters.hpp"

TEST_CASE("load_mdb_from_toml fails on non-toml format")
{
    std::filesystem::path json_file("./test_data/databases/example_monster_database.json");
    CHECK(DSDR::load_monster_from_toml(json_file) == 0);
}


TEST_CASE("load_mdb_from_toml successfully loads")
{
    std::filesystem::path toml_file("./test_data/databases/example_monster_database.toml");
    
    CHECK(DSDR::load_monster_from_toml(toml_file) == 1);
}
