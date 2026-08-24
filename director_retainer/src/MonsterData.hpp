import std;

#include "DSEnums.hpp"

namespace DSDR
{
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
        u16 m_damage_taken = 0;
        u16 m_effects_ended = 0;
    }

    struct Trait
    {
        // No bloody idea of what to put in here
        Trait::Condition m_condition;
        std::string m_special_condition;
        // figure out some fancy way of the traits having an effect on everything
    };

    struct MonsterEntry
    {
        std::string m_name;
        std::string m_id; // not sure of this yet
        Creature::Organization m_org;
        Creature::Role m_role;
        u16 m_encounter_value = 0;
        u16 m_death = 0;
        u16 m_creature_keyword = 0;
        u16 m_level = 1;
        Size m_size;
        u16 m_speed;
        u16 m_stability;
        u16 m_stamina;
        u16 m_free_strike; 
        u16 m_immunity = DamageTypes::None;
        u16 m_weakness = DamageTypes::None;
        Characteristics m_characteristics;
        u16 m_turns_per_round = 1;
        u16 m_triggers_per_round = 1;
        EndEffect m_end_effect;
        std::vector<ActionEntry> m_abilities;
        std::vector<ActionEntry> m_villian_actions;
        std::vector<ActionEntry> m_malice_actions;
        std::vector<Trait> m_traits;

    }
}