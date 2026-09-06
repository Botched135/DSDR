expoirt module dsdb:toml_extractors;

import :converts;
import :toml_helpers;

export namespace DSDR
{
    Creature::Size extract_size(const toml::node_view& in_node_view)
    {
        std::string size_str = extract_str_lowcase(in_node_view);
        std::size_t pos = 0;
        i32 space = std::stoi(size_str, &pos);

        return {static_cast<u8>(space), pos < size_str.size() ? convert_char_to_enum(size_str[pos]) : Creature::Size::Medium};
    }

    Creature::Characteristics extract_characteristics(const toml::node_view& in_node_view)
    {
        return {extract_val<i8>(in_node_view["might"]), extract_val<i8>(in_node_view["agility"]), extract_val<i8>(in_node_view["reason"]),
        extract_val<i8>(in_node_view["intuition"]), extract_val<i8>(in_node_view["presence"]), };
    }

    Creature::EndEffect extract_end_effect(const toml::node_view& in_node_view)
    {
        return {extract_val_or<u8>(in_node_view["damage"], 0), extract_val_or<u8>(in_node_view["count"], 0)};
    }

    Creature::resilience_array extract_damage_type_resilience(const toml::node_view& in_immunities, const toml::node_view& in_weaknesses)
    {
        Creature::resilience_array result;

        if(toml::array* immunities = in_immunities.as_array())
        {
            for(auto&& entry : *immunities)
            {
                auto& immunity = *entry.as_table();
                const u32 index = static_cast<u32>(extract_enum_from_str<Creature::DamageTypeResilience>(immunity["type"]));
                result[index].m_immunity = extract_val<u8>(immunity["value"]);
            }
        }

        if(toml::array* weaknesses = in_weaknesses.as_array())
        {
            for(auto&& entry : *weaknesses)
            {   
                auto& weakness = *entry.as_table();
                const u32 index = static_cast<u32>(extract_enum_from_str<Creature::DamageTypeResilience>(weakness["type"]));
                result[index].m_weakness = extract_val<u8>(weakness["value"]);
            }
        }

        return result;
    }

    Action::RollVariant extract_roll(const toml::node_view& in_roll)
    {
        if(auto* roll_tbl = in_roll.as_table())
        {
            toml::table& roll_entry = *roll_tbl;
            Action::Roll roll_type = extract_enum_from_str<Action::Roll>(roll_entry["type"]);

            switch (roll_type)
            {
            case Action::Roll::Power:
                return {extract_val<i8>(roll_entry["bonus"])};
            case Action::Roll::Test:
                return {extract_enum_from_str<Creature::Characteristic>(roll_entry["characteristic"])};
            default:
                return {};
            }
        }
        return {};
    }

    Action::Range extract_range(const toml::node_view& in_range)
    {
        if(toml::table* range = in_range.as_table())
        {
            auto& range_tbl = *range;

            return { extract_enum_from_str<Action::Distance>(range_tbl["type"]), 
                    extract_val_or<u16>(range_tbl["length"], 0u),
                    extract_val_or<u16>(range_tbl["width"], 0u)};
        }
        return {};
    }

    Targeting extract_targeting(const toml::node_view& in_targeting)
    {
        auto& targeting_tbl = *(in_targeting.as_table());

        return {extract_flags<TargetingFlags, u16>(targeting_tbl["type"]), 
                extract_val_or<u16>(targeting_tbl["count"], 0)};
    }


    Damage extract_damage(const toml::node_view& in_damage)
    {
        if(auto* damage_ptr = in_damage.as_table())
        {
            auto& damage_tbl = *damage_ptr;
            return {extract_val_or<u16>(damage_tbl["amount"],0),
                    extract_enum_from_str_or<DamageType>(damage_tbl["type"], DamageType::None)
            };
        }
        return {};
    }

    // TODO: Should potency be optional? That might be preferable for all that has a "default"
    std::vector<Action::Potency> extract_potencies(const toml::node_view& in_potencies)
    {
        if(auto* potencies = in_potencies.as_array())
        {
            std::vector<Action::Potency> results;
            results.reserve(potencies->size());
            for(auto&& entry : *potencies)
            {
                auto& potency_tbl = *entry.as_table(); 
                results.emplace_back
                (
                    extract_enum_from_str<Creature::Characteristic>(potency_tbl["characteristic"]),
                    extract_damage(potency_tbl["damage"]),
                    extract_val<std::string>(potency_tbl["effect"]),
                    extract_val<i8>(potency_tbl["resist"]),
                    extract_val_or<bool>(potency_tbl["replace_effect"], false)
                );
            }
        }
        return {};
    }

    std::vector<Action::Outcome> extract_outcomes(const toml::node_view& in_outcomes)
    {
        if(toml::array* outcomes = in_outcomes.as_array())
        {
            std::vector<Action::Outcome> result;
            result.reserve(outcomes->size());

            for(auto&& entry : *outcomes)
            {
                auto& outcome_tbl = *entry.as_table();
                fmt::print("Outcomes\n");
                result.emplace_back(
                    extract_damage(outcome_tbl["damage"]),
                    extract_potencies(outcome_tbl["potencies"]),
                    extract_val_or<std::string>(outcome_tbl["effect"], "")
                );
            }
        }

        return{};
    }

    Cooldown extract_cooldown(const toml::node_view& in_cooldown)
    {
        if(toml::table* cooldown = in_cooldown.as_table())
        {
            auto& cooldown_tbl = *cooldown;
            return {extract_val<i16>(cooldown_tbl["duration"]), extract_val_or<bool>(cooldown_tbl["global"], false)};
        }

        return {};
    }

    MaliceCost extract_malice_cost(const toml::node_view& in_malice_cost)
    {
        if(auto* malice_cost = in_malice_cost.as_table())
        {
            auto& malice_cost_tbl = *malice_cost;
            
            return { extract_val_or<u16>(malice_cost_tbl["base_cost"], 0),
                        extract_val_or<u16>(malice_cost_tbl["max_cost"], 0),
                        extract_val_or<u16>(malice_cost_tbl["step_cost"],0)

            };
        }
        return {};
    }
    std::vector<Effect> extract_effects(const toml::node_view& in_effects)
    {
        if(auto* effects = in_effects.as_array())
        {
            std::vector<Effect> result;
            result.reserve(effects->size());
            for(auto&& entry : *effects)
            {
                auto& effect = *entry.as_table();
                result.emplace_back(
                    extract_malice_cost(effect["malice_cost"]),
                    extract_damage(effect["damage"]),
                    extract_potencies(effect["potencies"]),
                    extract_val<std::string>(effect["effect"])
                );
            }

            return result;
        }

        return {};
    }

    std::vector<ActionEntry> extract_actions(const toml::node_view& in_actions, const Action::Type in_default = Action::Type::Main)
    {
        if(toml::array* actions = in_actions.as_array())
        {
            std::vector<ActionEntry> action_vec;
            action_vec.reserve(actions->size());
            
            for(auto&& entry : *actions)
            {
                auto& action_tbl = *entry.as_table();
                
                std::string name = extract_val<std::string>(action_tbl["name"]);
                Action::RollVariant roll = extract_roll(action_tbl["roll"]);
                u16 keyword_flags = extract_flags<Action::KeywordFlags>(action_tbl["tags"]);
                Action::Range range = extract_range(action_tbl["range"]);
                Action::Targeting targeting = extract_targeting(action_tbl["targeting"]);
                Action::Type action_type = extract_enum_from_str_or<Action::Type>(action_tbl["action_type"], in_default);
                bool is_signature = action_tbl["is_signature"].value_or(false);
                
                bool tiers_required =!std::holds_alternative<std::monostate>(roll);
                
                // outcomes are ordered after tier on what the relevant character rolls. So for tests, it is the first outcome that has highest damage and reverse for power roll
                std::vector<Action::Outcome> outcomes = extract_outcomes(action_tbl["outcomes"]);
                std::vector<Action::Effect> additional_effects = extract_effects(action_tbl["effects"]);
                Action::Cooldown cooldown = extract_cooldown(action_tbl["cooldown"]);
                Action::MaliceCost malice_cost = extract_malice_cost(action_tbl["malice_cost"]);
                std::string special = extract_val_or<std::string>(action_tbl["special"], "");
                std::string trigger = extract_val_or<std::string>(action_tbl["trigger"], "");

                action_vec.emplace_back
                (
                    name,
                    roll,
                    keyword_flags,
                    range,
                    targeting,
                    action_type,
                    trigger,
                    std::move(outcomes),
                    special,
                    malice_cost,
                    std::move(additional_effects),
                    cooldown,
                    is_signature
                );
            }

            return action_vec;
        }

        return {};
    } 

    std::vector<Creature::Trait> extract_traits(const toml::node_view& in_traits)
    {
        if(auto* traits_ptr = in_traits.as_array())
        {
            std::vector<Creature::Trait> result;
            result.reserve(traits_ptr->size());

            for(auto&& entry : *traits_ptr)
            {
                auto& trait_tbl = *entry.as_table();
                result.emplace_back(
                    extract_val<std::string>(trait_tbl["name"]),
                    extract_val<std::string>(trait_tbl["effect"]));
            }

            return result;
        }

        return {};
    }
}