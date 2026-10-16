module;

#include <filesystem>
#include <variant>

export module dsdb;
import utility;
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
        enum class Organization : u8;
        enum class Role : u8;
        enum class Characteristic : u8;
        enum class ConditionFlags : u16;
        enum class MovementFlags : u8;
        enum class KeywordFlags : u32;
        enum class SizeClass : u8;
        enum class DamageTypeResilience : u8;

        
        struct Resilience;
        struct Size;
        struct Characteristics;
        struct EndEffect;
        struct Trait;

        using resilience_array = std::array<Resilience, static_cast<u32>(10/*Creature::DamageTypeResilience::ENUM_COUNT*/)>;
        
    }

    namespace Action
    {
        enum class KeywordFlags : u8;
        enum class Roll : u8;
        enum class Type : u8;
        enum class Distance : u8;
        enum class Activation : u8;
        enum class TargetingFlags : u8;

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

    enum class DamageType : u8;
    enum class EffectEnd : u8;

    struct ActionEntry;
    struct MonsterEntry;

}