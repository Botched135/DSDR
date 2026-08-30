#pragma once
#include "DSDR/utility/type_defs.hpp"

namespace DSDR
{
    namespace Creature
    {
        enum class Organization
        {
            Minion,
            Horde,
            Platoon,
            Elite,
            Leader,
            Solo,

            ENUM_COUNT
        };

        enum class Role
        {
            Ambusher,
            Artillery,
            Brute,
            Controller,
            Defender,
            Harrier,
            Hexer,
            Leader,
            Mount,
            Solo,
            Support,

            ENUM_COUNT
        };

        enum class Characteristic
        {
            Might,
            Agility,
            Reason,
            Inuition,
            Presence,

            ENUM_COUNT
        };

        enum class ConditionFlags
        {
            None = 0,
            Bleeding = 1,
            Dazed = 1 << 1,
            Frightened = 1 << 2,
            Grabbed = 1 << 3,
            Prone = 1 << 4,
            Restrained = 1 << 5,
            Slowed = 1 << 6,
            Taunted = 1 << 7,
            Uncouncious = 1 << 8,
            Weakened = 1 << 9,
            Special = 1 << 10 // Have a list of additional special conditions, so if this flag is set, it will check the list
        };

        enum class MovementFlags
        {
            None = 0,
            Burrow = 1,
            Climb = 1 << 1,
            Flying = 1 << 2,
            Hover = 1 << 3,
            Swim = 1 << 4,
            Teleport = 1 << 5
        };

        enum class KeywordFlags
        {
            None = 0,
            Abyssal = 1,
            Accursed = 1 << 1,
            Animal = 1 << 2,
            Beast = 1 << 3,
            Construct = 1 << 4,
            Dragon = 1 << 5,
            Elemental = 1 << 6,
            Fey = 1 << 7, 
            Giant = 1 << 8,
            Horror = 1 << 9,
            Humanoid = 1 << 10,
            Infernal = 1 << 11,
            Ooze = 1 << 12,
            Plant = 1 << 13,
            Soulless = 1 << 14,
            Swarm = 1 << 15,
            Undead = 1 << 16
        };

        enum class Size
        {
            Tiny,
            Small,
            Medium,
            Large
        };

    }

    namespace Action
    {
        enum class KeywordFlags
        {
            None = 0,
            Area = 1,
            Charge = 1 << 1,
            Magic = 1 << 2,
            Melee = 1 << 3,
            Psionic = 1 << 4,
            Ranged = 1 << 5,
            Strike = 1 << 6,
            Weapon = 1 << 7
        };

        // Good idea to make this a variant with visitor
        enum class Roll
        {
            None,
            Power,
            Test,
        };

        enum class Type
        {
            Main, 
            Manuever,
            Movement,
            Trigger,
            FreeManuever,
            FreeTrigger  
        };

        enum class Distance // Having the both area of effect and regular distance in one makes it so that the struct can hold two ints for range no matter the type and then use as many as it needs 
        {
            Melee,
            Ranged,
            MeleeOrRanged,
            Self,
            Aura,
            Burst,
            Cube,
            Line,
            Wall,
            Special // This is for special monster only abilities
        };

        enum class Activation
        {
            StartOfTurn,
            EndOfTurn,
            StartOfRound,
            EndOfRound,
            StartOfEncounter,
            Special
        };

        enum class Resource
        {
            Heroic,
            Malice
        };
    }

    // If the target count is 0 it is considered each target, so default to 0
    enum class TargetFlags
    {
        Creature = 1,
        Object = 1 << 1,
        Enemy = 1 << 2,
        Ally = 1 << 3,
        Self = 1 << 4
    };
    enum class DamageType
    {
        None, // SHOULD BE DEFAULT
        Acid,
        Cold,
        Corruption,
        Fire,
        Holy,
        Lightning,
        Poison,
        Psychic,
        Sonic,

        ENUM_COUNT,  
    };

    enum class DamageTypeFlag
    {
        None = 0,
        Acid = 1,
        Cold = 1 << 1,
        Corruption = 1 << 2,
        Fire = 1 << 3,
        Holy = 1 << 4,
        Lightning = 1 << 5,
        Poison = 1 << 6,
        Psychic = 1 << 7,
        Sonic = 1 << 8,

        ENUM_COUNT = 9,
        All = (1 << ENUM_COUNT) - 1    
    };

    enum class EffectEnd 
    {
        EndOfTurn,
        SaveEnds,
        EndOfEncounter
    };
}