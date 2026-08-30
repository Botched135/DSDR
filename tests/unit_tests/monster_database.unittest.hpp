#pragma once

#include <doctest.h>
#include "DSDR/database/monster_db.hpp"
#include "DSDR/ds_enum_converters.hpp"

TEST_CASE("load_mdb_from_file fails on non-toml format")
{
    std::filesystem::path json_file("./test_data/databases/example_monster_database.json");
    CHECK(DSDR::load_monster_from_file(json_file) == 0);
}


TEST_CASE("load_mdb_from_file successfully loads")
{
    std::filesystem::path toml_file("./test_data/databases/example_monster_database.toml");
    
    CHECK(DSDR::load_monster_from_file(toml_file) == 1);
}
