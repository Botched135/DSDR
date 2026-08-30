#pragma once
#include "DSDR/data/ds_enums.hpp"
#include <string>

namespace DSDR
{
    struct PowerRoll
    {
        Action::Roll m_roll = Action::Roll::Power;
        u8 m_damage;
    };

    struct Potency
    {
        Creature::Characteristic m_test_characteristic;
        u8 m_resist_threshold;
        std::string m_effect;

    };

    struct Range
    {
        Action::Distance m_type;
        u16 m_first_distance = 0;
        u16 m_second_distance = 0;
    };

    struct ResourceCost
    {
        Action::Resource m_resource = Action::Resource::Malice;
        u16 m_min_cost = 0;
        u16 m_max_cost = 0; // if max_cost is higher than min, you can use additional     
    };

    struct Cooldown 
    {
        u16 m_duration = 0;
        bool m_is_individual = true;
    };

    struct ActionEntry
    {
        std::string m_name;
        std::string m_power_roll;
        u16 m_keywords = static_cast<u16>(Action::KeywordFlags::None);
        Range m_range;
        std::string m_target;
        Action::Type m_type = Action::Type::Main;
        std::string m_trigger;
        std::string m_low_tier; // possibily add this to effect and slice it up with string_views 
        std::string m_medium_tier;
        std::string m_high_tier;
        std::string m_effect;
        std::string m_special;
        ResourceCost m_resource_cost;
        Cooldown m_cooldown;
        bool is_signature = false;
    };
}