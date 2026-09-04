#pragma once
#include "DSDR/data/ds_enums.hpp"
#include "DSDR/data/action_data.hpp"
#include <string>
#include <vector>
#include <array>

namespace DSDR
{
    struct Resilience
    {
        u8 m_immunity;
        u8 m_weakness;
    };

    using resilience_array = std::array<Resilience, static_cast<u32>(Creature::DamageTypeResilience::ENUM_COUNT)>;

    struct Size
    {
        u8 m_space = 1;
        Creature::Size m_size_rating = Creature::Size::Tiny; 
    };

    struct Characteristics
    {
        i8 m_might = 0;
        i8 m_agility = 0;
        i8 m_reason = 0;
        i8 m_intuition = 0;
        i8 m_presence = 0;
    };

    struct EndEffect 
    {
        u8 m_damage_taken = 0;
        u8 m_effects_ended = 0;
    };

    struct Trait
    {
        // No bloody idea of what to put in here
        //Trait::Condition m_condition;
        std::string m_name;
        std::string m_effect;
        //std::string m_special_condition;
        // figure out some fancy way of the traits having an effect on everything
    };

    struct MonsterEntry
    {
        std::string m_name;
        std::string m_id; // not sure of this yet
        Creature::Organization m_org;
        Creature::Role m_role;
        u32 m_types = static_cast<u32>(Creature::KeywordFlags::None);
        u16 m_encounter_value = 0;
        i16 m_death = 0;
        u16 m_level = 1;
        Size m_size;
        u16 m_speed;
        u16 m_stability;
        u16 m_stamina;
        u16 m_free_strike;
        std::string m_captain_bonus;
        resilience_array m_resilience;
        Characteristics m_characteristics;
        u16 m_turns_per_round = 1;
        u16 m_triggers_per_round = 1;
        EndEffect m_end_effect;
        std::vector<ActionEntry> m_abilities;
        std::vector<ActionEntry> m_villian_actions;
        std::vector<ActionEntry> m_malice_actions;
        std::vector<Trait> m_traits;
    };
}