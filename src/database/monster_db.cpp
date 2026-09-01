#include "DSDR/database/monster_db.hpp"
#include "DSDR/data/monster_data.hpp"
#include "DSDR/data/action_data.hpp"
#include "DSDR/ds_enum_converters.hpp"
#include "DSDR/toml_helpers.hpp"
#include <fmt/core.h>
#include <toml++/toml.hpp>
#include <iostream>
#include <string_view>
#include <stacktrace>

namespace DSDR
{
    constexpr const char* s_toml_ext =".toml";

    namespace // Helper functions
    {
        Size extract_size(const node_view& in_node_view)
        {
            std::string size_str = extract_str_lowcase(in_node_view);
            std::size_t pos = 0;
            i32 space = std::stoi(size_str, &pos);

            return {static_cast<u8>(space), pos < size_str.size() ? convert_char_to_enum(size_str[pos]) : Creature::Size::Medium};
        }

        Characteristics extract_characteristics(const node_view& in_node_view)
        {
            return {extract_val<i8>(in_node_view["might"]), extract_val<i8>(in_node_view["agility"]), extract_val<i8>(in_node_view["reason"]),
            extract_val<i8>(in_node_view["intuition"]), extract_val<i8>(in_node_view["presence"]), };
        }

        EndEffect extract_end_effect(const node_view& in_node_view)
        {
            return {extract_val_or<u8>(in_node_view["damage"], 0), extract_val_or<u8>(in_node_view["count"], 0)};
        }

        resilience_array extract_damage_type_resilience(const node_view& in_immunities, const node_view& in_weaknesses)
        {
            resilience_array result;

            if(toml::array* immunities = in_immunities.as_array())
            {
                for(auto&& entry : *immunities)
                {
                    auto& immunity = *entry.as_table();
                    const u32 index = static_cast<u32>(extract_enum_from_str<Creature::DamageTypeResilience>(immunity["type"]));
                    result[index].m_immunity = extract_val<u8>(immunity["value"]);
                }
            }

            if(toml::array* weaknesses = in_weaknesses.as_array())
            {
                for(auto&& entry : *weaknesses)
                {   
                    auto& weakness = *entry.as_table();
                    const u32 index = static_cast<u32>(extract_enum_from_str<Creature::DamageTypeResilience>(weakness["type"]));
                    result[index].m_weakness = extract_val<u8>(weakness["value"]);
                }
            }

            return result;
        }

        RollVariant extract_roll(const node_view& in_roll)
        {
            if(auto* roll_tbl = in_roll.as_table())
            {
                toml::table& roll_entry = *roll_tbl;
                Action::Roll roll_type = extract_enum_from_str<Action::Roll>(roll_entry["type"]);

                switch (roll_type)
                {
                case Action::Roll::Power:
                    return {extract_val<i8>(roll_entry["bonus"])};
                case Action::Roll::Test:
                    return {extract_enum_from_str<Creature::Characteristic>(roll_entry["characteristic"])};
                default:
                    return {};
                }
            }
            return {};
        }

        Range extract_range(const node_view& in_range)
        {
            if(toml::table* range = in_range.as_table())
            {
                auto& range_tbl = *range;

                return { extract_enum_from_str<Action::Distance>(range_tbl["type"]), 
                        extract_val_or<u16>(range_tbl["length"], 0u),
                        extract_val_or<u16>(range_tbl["width"], 0u)};
            }
            return {};
        }

        Targeting extract_targeting(const node_view& in_targeting)
        {
            auto& targeting_tbl = *(in_targeting.as_table());

            return {extract_flags<TargetingFlags, u16>(targeting_tbl["type"]), extract_val_or<u16>(targeting_tbl["count"], 0)};
        }

        // TODO: Should potency be optional? That might be preferable for all that has a "default"
        Potency extract_potency(const node_view& in_potency)
        {
            if(toml::table* potency = in_potency.as_table())
            {
                fmt::print("Potency\n");
                auto& potency_tbl = *potency;

                return {extract_enum_from_str<Creature::Characteristic>(potency_tbl["characteristic"]),
                        extract_val<std::string>(potency_tbl["effect"]),
                        extract_val<i8>(potency_tbl["resist"])};

            }
            return {};
        }

        std::vector<Outcome> extract_outcomes(const node_view& in_outcomes)
        {
            if(toml::array* outcomes = in_outcomes.as_array())
            {
                std::vector<Outcome> result;
                result.reserve(outcomes->size());

                for(auto&& entry : *outcomes)
                {
                    auto& outcome_tbl = *entry.as_table();
                    fmt::print("Outcomes\n");
                    result.emplace_back(
                        extract_val<u16>(outcome_tbl["damage"]),
                        extract_enum_from_str<DamageType>(outcome_tbl["damage_type"]),
                        extract_potency(outcome_tbl["potency"]),
                        extract_val<std::string>(outcome_tbl["effect"])
                    );
                }
            }

            return{};
        }

        std::vector<ActionEntry> extract_actions(const node_view& in_actions)
        {
            if(toml::array* actions = in_actions.as_array())
            {
                std::vector<ActionEntry> action_vec;
                action_vec.reserve(actions->size());
                
                for(auto&& entry : *actions)
                {
                    auto& action_tbl = *entry.as_table();
                    
                    std::string name = extract_val<std::string>(action_tbl["name"]);
                    fmt::print("Handling {}\n", name);
                    RollVariant roll = extract_roll(action_tbl["roll"]);
                    fmt::print("Roll done\n");
                    u16 keyword_flags = extract_flags<Action::KeywordFlags>(action_tbl["tags"]);
                    fmt::print("tags done\n");
                    Range range = extract_range(action_tbl["range"]);
                    fmt::print("Range done\n");
                    Targeting targeting = extract_targeting(action_tbl["targeting"]);
                    fmt::print("Targeting done\n");
                    Action::Type action_type = extract_enum_from_str<Action::Type>(action_tbl["action_type"]);
                    fmt::print("action type done\n");
                    bool is_signature = action_tbl["is_signature"].value_or(false);
                    fmt::print("Is signature\n");
                    
                    bool tiers_required =!std::holds_alternative<std::monostate>(roll);
                    
                    // outcomes are ordered after tier on what the relevant character rolls. So for tests, it is the first outcome that has highest damage and reverse for power roll
                    std::vector<Outcome> outcomes = extract_outcomes(action_tbl["outcomes"]);
                    // Cooldown
                    
                    //ResourceCost
                }

                return action_vec;
            }

            return {};
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
                for(auto&& entry : *monsters)
                {
                    // TODO: the exception that is thrown needs to be useful
                    auto& monster_tbl = *entry.as_table();
                    // each of them are tables
                    std::string name = extract_val<std::string>(monster_tbl["name"]);
                    Creature::Organization org = extract_enum_from_str<Creature::Organization>(monster_tbl["creature_org"]);
                    Creature::Role role = extract_enum_from_str<Creature::Role>(monster_tbl["creature_role"]);
                    u16 encounter_value = extract_val<u16>(monster_tbl["encounter_value"]); // No defaults
                    i16 death = monster_tbl["death"].value_or(0);
                    u32 types = extract_flags<Creature::KeywordFlags>(monster_tbl["types"]);
                    u16 level = extract_val<u16>(monster_tbl["level"]);
                    Size size = extract_size(monster_tbl["size"]);
                    u16 speed = extract_val<u16>(monster_tbl["speed"]);
                    u16 stamina = extract_val<u16>(monster_tbl["stamina"]);
                    u16 stability = extract_val<u16>(monster_tbl["stability"]);
                    u16 free_strike = extract_val<u16>(monster_tbl["free_strike"]);
                    
                    resilience_array resilience = extract_damage_type_resilience(monster_tbl["immunity"], monster_tbl["weakness"]);
                    
                    u16 movement = extract_flags<Creature::MovementFlags>(monster_tbl["movement"]);
                    
                    Characteristics characteristics = extract_characteristics(monster_tbl["characteristics"]);

                    u16 turns_per_round = monster_tbl["turns_per_round"].value_or(1);
                    u16 triggers_per_round = monster_tbl["triggers_per_round"].value_or(1);
                    EndEffect end_effect = extract_end_effect(monster_tbl["end_effect"]);
                    std::vector<ActionEntry> abilities = extract_actions(monster_tbl["abilities"]);
                    // Abilities
                    // Villian_actions
                    // malice_actions
                    // traits 
                    // Captain bonus

                    fmt::print("Done with {}\n", name);
                    

                    

                }
            }
            catch(std::bad_optional_access& ex)
            {
                fmt::print("{}\n",std::to_string(std::stacktrace::current()));
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