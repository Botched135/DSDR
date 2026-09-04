#include "DSDR/ds_enum_converters.hpp"

#include <fmt/core.h>

namespace DSDR
{
    void initialize_enum_maps()
    {
        // Organization
        org_map["minion"] = Creature::Organization::Minion;
        org_map["horde"] = Creature::Organization::Horde;
        org_map["platoon"] = Creature::Organization::Platoon;
        org_map["elite"] = Creature::Organization::Elite;
        org_map["leader"] = Creature::Organization::Leader;
        org_map["solo"] = Creature::Organization::Solo;

        // Role
        role_map["ambusher"] = Creature::Role::Ambusher;
        role_map["artillery"] = Creature::Role::Artillery;
        role_map["brute"] = Creature::Role::Brute;
        role_map["controller"] = Creature::Role::Controller;
        role_map["defender"] = Creature::Role::Defender;
        role_map["harrier"] = Creature::Role::Harrier;
        role_map["hexer"] = Creature::Role::Hexer;
        role_map["leader"] = Creature::Role::Leader;
        role_map["mount"] = Creature::Role::Mount;
        role_map["solo"] = Creature::Role::Solo;
        role_map["support"] = Creature::Role::Support;

        // Characteristics
        characteristics_map["might"] = Creature::Characteristic::Might;
        characteristics_map["agility"] = Creature::Characteristic::Agility;
        characteristics_map["reason"] = Creature::Characteristic::Reason;
        characteristics_map["intuition"] = Creature::Characteristic::Inuition;
        characteristics_map["presence"] = Creature::Characteristic::Presence;

        // Condition
        condition_map["none"]        = Creature::ConditionFlags::None;
        condition_map["bleeding"]    = Creature::ConditionFlags::Bleeding;
        condition_map["dazed"]       = Creature::ConditionFlags::Dazed;
        condition_map["frightened"]  = Creature::ConditionFlags::Frightened;
        condition_map["grabbed"]     = Creature::ConditionFlags::Grabbed;
        condition_map["prone"]       = Creature::ConditionFlags::Prone;
        condition_map["restrained"]  = Creature::ConditionFlags::Restrained;
        condition_map["slowed"]      = Creature::ConditionFlags::Slowed;
        condition_map["taunted"]     = Creature::ConditionFlags::Taunted;
        condition_map["unconscious"] = Creature::ConditionFlags::Uncouncious;
        condition_map["weakened"]    = Creature::ConditionFlags::Weakened;
        condition_map["special"]     = Creature::ConditionFlags::Special;

        // Movement
        movement_map["none"]     = Creature::MovementFlags::None;
        movement_map["burrow"]   = Creature::MovementFlags::Burrow;
        movement_map["climb"]    = Creature::MovementFlags::Climb;
        movement_map["flying"]   = Creature::MovementFlags::Flying;
        movement_map["hover"]    = Creature::MovementFlags::Hover;
        movement_map["swim"]     = Creature::MovementFlags::Swim;
        movement_map["teleport"] = Creature::MovementFlags::Teleport;

        // Keywords
        creature_keyword_map["abyssal"]   = Creature::KeywordFlags::Abyssal;
        creature_keyword_map["accursed"]  = Creature::KeywordFlags::Accursed;
        creature_keyword_map["animal"]    = Creature::KeywordFlags::Animal;
        creature_keyword_map["beast"]     = Creature::KeywordFlags::Beast;
        creature_keyword_map["construct"] = Creature::KeywordFlags::Construct;
        creature_keyword_map["dragon"]    = Creature::KeywordFlags::Dragon;
        creature_keyword_map["elemental"] = Creature::KeywordFlags::Elemental;
        creature_keyword_map["fey"]       = Creature::KeywordFlags::Fey;
        creature_keyword_map["giant"]     = Creature::KeywordFlags::Giant;
        creature_keyword_map["horror"]    = Creature::KeywordFlags::Horror;
        creature_keyword_map["humanoid"]  = Creature::KeywordFlags::Humanoid;
        creature_keyword_map["infernal"]  = Creature::KeywordFlags::Infernal;
        creature_keyword_map["ooze"]      = Creature::KeywordFlags::Ooze;
        creature_keyword_map["plant"]     = Creature::KeywordFlags::Plant;
        creature_keyword_map["soulless"]  = Creature::KeywordFlags::Soulless;
        creature_keyword_map["swarm"]     = Creature::KeywordFlags::Swarm;
        creature_keyword_map["undead"]    = Creature::KeywordFlags::Undead;

        // Damage Types Resilience
        damage_type_resilience_map["acid"]       = Creature::DamageTypeResilience::Acid;
        damage_type_resilience_map["cold"]       = Creature::DamageTypeResilience::Cold;
        damage_type_resilience_map["corruption"] = Creature::DamageTypeResilience::Corruption;
        damage_type_resilience_map["fire"]       = Creature::DamageTypeResilience::Fire;
        damage_type_resilience_map["holy"]       = Creature::DamageTypeResilience::Holy;
        damage_type_resilience_map["lightning"]  = Creature::DamageTypeResilience::Lightning;
        damage_type_resilience_map["poison"]     = Creature::DamageTypeResilience::Poison;
        damage_type_resilience_map["psychic"]    = Creature::DamageTypeResilience::Psychic;
        damage_type_resilience_map["sonic"]      = Creature::DamageTypeResilience::Sonic;
        damage_type_resilience_map["all"]        = Creature::DamageTypeResilience::All;

        // Size
        size_map['t'] = Creature::Size::Tiny;
        size_map['s'] = Creature::Size::Small;
        size_map['m'] = Creature::Size::Medium;
        size_map['l'] = Creature::Size::Large;

        // Action Keywords
        action_keyword_map["area"]    = Action::KeywordFlags::Area;
        action_keyword_map["charge"]  = Action::KeywordFlags::Charge;
        action_keyword_map["magic"]   = Action::KeywordFlags::Magic;
        action_keyword_map["melee"]   = Action::KeywordFlags::Melee;
        action_keyword_map["psionic"] = Action::KeywordFlags::Psionic;
        action_keyword_map["ranged"]  = Action::KeywordFlags::Ranged;
        action_keyword_map["strike"]  = Action::KeywordFlags::Strike;
        action_keyword_map["weapon"]  = Action::KeywordFlags::Weapon;

        // Action Type
        action_type_map["main"]           = Action::Type::Main;
        action_type_map["maneuver"]       = Action::Type::Manuever;
        action_type_map["movement"]       = Action::Type::Movement;
        action_type_map["trigger"]        = Action::Type::Trigger;
        action_type_map["free_maneuver"]  = Action::Type::FreeManuever;
        action_type_map["free_trigger"]   = Action::Type::FreeTrigger;
        action_type_map["villian"]        = Action::Type::Villian;
        action_type_map["malice"]         = Action::Type::Malice;

        // Action Distance
        action_distance_map["melee"]          = Action::Distance::Melee;
        action_distance_map["ranged"]         = Action::Distance::Ranged;
        action_distance_map["melee_or_ranged"]= Action::Distance::MeleeOrRanged;
        action_distance_map["self"]           = Action::Distance::Self;
        action_distance_map["aura"]           = Action::Distance::Aura;
        action_distance_map["burst"]          = Action::Distance::Burst;
        action_distance_map["cube"]           = Action::Distance::Cube;
        action_distance_map["line"]           = Action::Distance::Line;
        action_distance_map["wall"]           = Action::Distance::Wall;
        action_distance_map["special"]        = Action::Distance::Special;

        // Action Resource
        action_resource_map["heroic"] = Action::Resource::Heroic;
        action_resource_map["malice"] = Action::Resource::Malice;

        // Action Activation
        action_activation_map["start_of_turn"]      = Action::Activation::StartOfTurn;
        action_activation_map["end_of_turn"]        = Action::Activation::EndOfTurn;
        action_activation_map["start_of_round"]     = Action::Activation::StartOfRound;
        action_activation_map["end_of_round"]       = Action::Activation::EndOfRound;
        action_activation_map["start_of_encounter"] = Action::Activation::StartOfEncounter;
        action_activation_map["special"]            = Action::Activation::Special;

        action_roll_map["power"] = Action::Roll::Power;
        action_roll_map["test"] = Action::Roll::Test;

        // Damage Types
        damage_type_map["acid"]       = DamageType::Acid;
        damage_type_map["cold"]       = DamageType::Cold;
        damage_type_map["corruption"] = DamageType::Corruption;
        damage_type_map["fire"]       = DamageType::Fire;
        damage_type_map["holy"]       = DamageType::Holy;
        damage_type_map["lightning"]  = DamageType::Lightning;
        damage_type_map["poison"]     = DamageType::Poison;
        damage_type_map["psychic"]    = DamageType::Psychic;
        damage_type_map["sonic"]      = DamageType::Sonic;

        // Effect End
        effect_end_map["end_of_turn"]      = EffectEnd::EndOfTurn;
        effect_end_map["save_ends"]        = EffectEnd::SaveEnds;
        effect_end_map["end_of_encounter"] = EffectEnd::EndOfEncounter;

        targeting_flag_map["creature"]  = TargetingFlags::Creature;
        targeting_flag_map["object"]    = TargetingFlags::Object;
        targeting_flag_map["enemy"]     = TargetingFlags::Enemy;
        targeting_flag_map["ally"]      = TargetingFlags::Ally;
        targeting_flag_map["self"]      = TargetingFlags::Self;
    }

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