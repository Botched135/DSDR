export module dsdb:converters;

import std;

export namespace DSDR
{
    template<typename T>
    T convert_str_to_enum(std::string_view in_str) = delete;

    template<typename T>
    T convert_str_to_enum_or(std::string_view in_str, const T in_default) = delete;


    template<>
    Creature::Organization convert_str_to_enum(std::string_view in_str)
    {
        return org_map[in_str];
    }

    template<>
    Creature::Role convert_str_to_enum(std::string_view in_str)
    {
        return role_map[in_str];
    }

    template<>
    Creature::KeywordFlags convert_str_to_enum(std::string_view in_str)
    {
        return creature_keyword_map[in_str];
    }

    template<>
    Creature::MovementFlags convert_str_to_enum(std::string_view in_str)
    {
        return movement_map[in_str];
    }

    template<>
    Creature::DamageTypeResilience convert_str_to_enum(std::string_view in_str)
    {
        return damage_type_resilience_map[in_str];
    }

    template<>
    Action::Roll convert_str_to_enum(std::string_view in_str)
    {
        return action_roll_map[in_str];
    }

    template<>
    Creature::Characteristic convert_str_to_enum(std::string_view in_str)
    {
        return characteristics_map[in_str];
    }

    template<>
    Action::Distance convert_str_to_enum(std::string_view in_str)
    {
        return action_distance_map[in_str];
    }

    template<>
    Action::KeywordFlags convert_str_to_enum(std::string_view in_str)
    {
        return action_keyword_map[in_str];
    }

    template<> 
    Action::Type convert_str_to_enum(std::string_view in_str)
    {
        return action_type_map[in_str];
    }

    template<>
    TargetingFlags convert_str_to_enum(std::string_view in_str)
    {
        return targeting_flag_map[in_str];
    }

    template<>
    DamageType convert_str_to_enum(std::string_view in_str)
    {
        return damage_type_map[in_str];
    }


    Creature::Size convert_char_to_enum(const char in_char)
    {
        return size_map[in_char];
    }

}