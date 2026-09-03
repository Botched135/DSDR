#pragma once
#include "DSDR/data/ds_enums.hpp"
#include <string>
#include <variant>
#include <vector>

namespace DSDR
{

    // All std::string m_effects needs to be replaced properly at some point
    using RollVariant = std::variant<std::monostate, i8, Creature::Characteristic>;

    struct Damage
    {
        u16 m_amount;
        DamageType m_type = DamageType::None;
    };

    struct Potency // removing the effect from potency as that should be part of the Outcome 
    {
        Creature::Characteristic m_test_characteristic;
        Damage m_damage;
        std::string m_effect;
        i8 m_resist_threshold;
        bool effect_in_addition = true; // If the potency goes through, the effects will be in addition to the ability's original effect. If false, it will replace original effect.
    };


    struct Range
    {
        Action::Distance m_type;
        u16 m_first_distance = 0;
        u16 m_second_distance = 0;
    };

    struct MaliceCost
    {
        u16 m_base_cost = 0;
        u16 m_max_cost = 0; // if max is 0, there is no max
        u16 m_step_cost = 0; // if step cost is zero, you cannot pay extra malice
    };

    struct Cooldown 
    {
        i16 m_duration = 0; // -1 for only once per encounter
        bool m_is_global = true;
    };
    
    struct Targeting
    {
        u16 m_target_flags = 0;
        u16 m_count = 0;
    };

    struct Outcome
    {
        Damage m_damage;
        std::vector<Potency> m_potency;
        std::string m_effect;
    };

    struct Effect
    {
        MaliceCost m_malice_cost;
        Damage m_damage;
        std::vector<Potency> m_potencies;
        std::string m_effect;
    };

    struct ActionEntry
    {
        std::string m_name;
        RollVariant m_roll; // use get<static_cast<u32>(m_roll)> to get the relevant type
        // use index() to figure what type of roll it is
        u16 m_keywords = static_cast<u16>(Action::KeywordFlags::None);
        Range m_range;
        std::string m_target;
        Action::Type m_type = Action::Type::Main;
        std::string m_trigger;
        std::vector<Outcome> m_outcomes;
        std::string m_special;
        MaliceCost m_malice_cost;
        std::vector<Effect> m_additional_effects;
        Cooldown m_cooldown;
        bool is_signature = false;
    };
}