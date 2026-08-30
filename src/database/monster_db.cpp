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

    namespace // Helper functions
    {
        Size handle_size(const node_view& in_node_view)
        {
            std::string size_str = extract_str(in_node_view);
            std::size_t pos = 0;
            i32 space = std::stoi(size_str, &pos);

            return {static_cast<u8>(space), pos < size_str.size() ? convert_char_to_enum(size_str[pos]) : Creature::Size::Medium};
        }

        Characteristics handle_characteristics(const node_view& in_node_view)
        {
            return {extract_val<i8>(in_node_view["might"]), extract_val<i8>(in_node_view["agility"]), extract_val<i8>(in_node_view["reason"]),
            extract_val<i8>(in_node_view["intuition"]), extract_val<i8>(in_node_view["presence"]), };
        }

        EndEffect handle_end_effect(const node_view& in_node_view)
        {
            return {extract_val_or<u8>(in_node_view["damage"], 0), extract_val_or<u8>(in_node_view["count"], 0)};
        }

        resilience_array handle_damage_type_resilience(const node_view& in_immunities, const node_view& in_weaknesses)
        {
            resilience_array result;

            if(toml::array* immunities = in_immunities.as_array())
            {
                for(auto&& entry : *immunities)
                {
                    auto& immunity = *entry.as_table();
                    const u32 index = static_cast<u32>(convert_str_to_enum<Creature::DamageTypeResilience>(extract_str(immunity["type"])));
                    result[index] |= extract_val<u8>(immunity["value"]) << 8;
                }
            }

            if(toml::array* weaknesses = in_weaknesses.as_array())
            {
                for(auto&& entry : *weaknesses)
                {   
                    auto& weakness = *entry.as_table();
                    const u32 index = static_cast<u32>(convert_str_to_enum<Creature::DamageTypeResilience>(extract_str(weakness["type"])));
                    result[index] |= extract_val<u8>(weakness["value"]);
                }
            }

            return result;
        }
    }

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
                    auto& table_entry = *entry.as_table();
                    // each of them are tables
                    std::string_view name = extract_val<std::string_view>(table_entry["name"]);
                    Creature::Organization org = convert_str_to_enum<Creature::Organization>(extract_str(table_entry["creature_org"]));
                    Creature::Role role = convert_str_to_enum<Creature::Role>(extract_str(table_entry["creature_role"]));
                    u16 encounter_value = extract_val<u16>(table_entry["encounter_value"]); // No defaults
                    i16 death = table_entry["death"].value_or(0);
                    u32 types = extract_flags<Creature::KeywordFlags>(table_entry["types"]);
                    u16 level = extract_val<u16>(table_entry["level"]);
                    Size size = handle_size(table_entry["size"]);
                    u16 speed = extract_val<u16>(table_entry["speed"]);
                    u16 stamina = extract_val<u16>(table_entry["stamina"]);
                    u16 stability = extract_val<u16>(table_entry["stability"]);
                    u16 free_strike = extract_val<u16>(table_entry["free_strike"]);
                    
                    resilience_array resilience = handle_damage_type_resilience(table_entry["immunity"], table_entry["weakness"]);
                    
                    u16 movement = extract_flags<Creature::MovementFlags>(table_entry["movement"]);
                    
                    Characteristics characteristics = handle_characteristics(table_entry["characteristics"]);

                    u16 turns_per_round = table_entry["turns_per_round"].value_or(1);
                    u16 triggers_per_round = table_entry["triggers_per_round"].value_or(1);
                    EndEffect end_effect = handle_end_effect(table_entry["end_effect"]);

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