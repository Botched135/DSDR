export module dsdb;

import std;

export namespace DSDR
{
    void initialize_enum_maps();

    i32 load_monster_from_toml(const std::filesystem::path& in_file_path);
    i32 load_monster_from_json(const std::filesystem::path& in_file_path);
}

export namespace DSDR
{
    namespace Creature
    {
        enum class Organization;
        enum class Role;
        enum class Characteristic;
        enum class ConditionFlags;
        enum class MovementFlags;
        enum class KeywordFlags;
        enum class Size;
        enum class DamageTypeResilience;

        
        struct Resilience;
        struct Size;
        struct Characteristics;
        struct EndEffect;
        struct Trait;

        using resilience_array = std::array<Resilience, static_cast<u32>(Creature::DamageTypeResilience::ENUM_COUNT)>;
        
    }

    namespace Action
    {
        enum class KeywordFlags;
        enum class Roll;
        enum class Type;
        enum class Distance;;
        enum class Activation;
        enum class TargetingFlags;

        using RollVariant = std::variant<std::monostate, i8, Creature::Characteristic>;
        struct Damage;
        struct Potency;
        struct Range;
        struct MaliceCost;
        struct Cooldown;
        struct Targeting;
        struct Outcome;
        struct Effect;
    }

    enum class DamageType;
    enum class EffectEnd;

    struct ActionEntry;
    struct MonsterEntry;

}