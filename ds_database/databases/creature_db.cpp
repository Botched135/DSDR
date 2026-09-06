module dsdb;

import utility;
import :extraction;
import :converts;
import std;
import fmt;

namespace DSDR
{
    constexpr const char* s_toml_ext =".toml";

    i32 load_monster_from_toml(const std::filesystem::path& in_file_path)
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
                    Creature::Size size = extract_size(monster_tbl["size"]);
                    u16 speed = extract_val<u16>(monster_tbl["speed"]);
                    u16 stamina = extract_val<u16>(monster_tbl["stamina"]);
                    u16 stability = extract_val<u16>(monster_tbl["stability"]);
                    u16 free_strike = extract_val<u16>(monster_tbl["free_strike"]);
                    
                    Creature::resilience_array resilience = extract_damage_type_resilience(monster_tbl["immunity"], monster_tbl["weakness"]);
                    
                    u16 movement = extract_flags<Creature::MovementFlags>(monster_tbl["movement"]);
                    
                    Creature::Characteristics characteristics = extract_characteristics(monster_tbl["characteristics"]);

                    u16 turns_per_round = monster_tbl["turns_per_round"].value_or(1);
                    u16 triggers_per_round = monster_tbl["triggers_per_round"].value_or(1);
                    EndEffect end_effect = extract_end_effect(monster_tbl["end_effect"]);
                    std::vector<ActionEntry> abilities = extract_actions(monster_tbl["abilities"]);
                    std::vector<ActionEntry> villian_actions = extract_actions(monster_tbl["villian_actions"], Action::Type::Villian);
                    std::vector<ActionEntry> malice_actions = extract_actions(monster_tbl["malice_actions"], Action::Type::Malice);
                    std::vector<Creature::Trait> traits = extract_traits(monster_tbl["traits"]);
                    std::string captain_bonus = extract_val_or<std::string>(monster_tbl["with_captain"], "");

                    fmt::print("Done with {}\n", name);
                    


                    MonsterEntry monster
                    {
                        name,
                        "",
                        org,
                        role,
                        types,
                        encounter_value,
                        death,
                        level,
                        size,
                        speed,
                        stability,
                        stamina,
                        free_strike,
                        captain_bonus,
                        resilience,
                        characteristics,
                        turns_per_round,
                        triggers_per_round,
                        end_effect,
                        std::move(abilities),
                        std::move(villian_actions),
                        std::move(malice_actions),
                        std::move(traits)
                    };
                    

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
}