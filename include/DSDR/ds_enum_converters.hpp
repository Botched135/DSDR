#pragma once

#include "DSDR/data/ds_enums.hpp"
#include <string_view>
#include <ankerl/unordered_dense.h>

namespace DSDR
{
    // Keep an eye on this.. string_view might cause trouble
    template<typename T> using enum_map = ankerl::unordered_dense::map<std::string_view, T>;


    namespace
    {
        static enum_map<Creature::Organization> org_map;
        static enum_map<Creature::Role> role_map;
        static enum_map<Creature::ConditionFlags> condition_map;
        static enum_map<Creature::MovementFlags> movement_map;
        static enum_map<Creature::KeywordFlags> creature_keyword_map;
        static enum_map<Creature::DamageTypeResilience> damage_type_resilience_map;
        static ankerl::unordered_dense::map<char, Creature::Size> size_map;

        static enum_map<Action::KeywordFlags> action_keyword_map;
        static enum_map<Action::Type> action_type_map;
        static enum_map<Action::Distance> action_distance_map;
        static enum_map<Action::Resource> action_resource_map;
        static enum_map<Action::Activation> action_activation_map;

        static enum_map<DamageType> damage_type_map;
        static enum_map<EffectEnd> effect_end_map;
    }



    void initialize_enum_maps();


    template<typename T>
    T convert_str_to_enum(std::string_view in_str) = delete;

    template<typename T>
    std::string convert_enum_to_str(T in_enum) = delete;

    template<>
    Creature::Organization convert_str_to_enum(std::string_view in_str);

    template<>
    Creature::Role convert_str_to_enum(std::string_view in_str);

    template<>
    Creature::KeywordFlags convert_str_to_enum(std::string_view in_str);

    template<>
    Creature::MovementFlags convert_str_to_enum(std::string_view in_str);

    template<>
    Creature::DamageTypeResilience convert_str_to_enum(std::string_view in_str);

    Creature::Size convert_char_to_enum(const char in_char);
}