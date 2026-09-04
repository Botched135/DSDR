#pragma once 
#include <toml++/toml.hpp>
#include "DSDR/data/monster_data.hpp"
#include "DSDR/data/action_data.hpp"
#include "DSDR/ds_enum_converters.hpp"
#include "DSDR/utility/concepts.hpp"
#include "DSDR/utility/algorithms.hpp"
#include <fmt/core.h>

namespace DSDR
{
    using node_view = toml::v3::node_view<toml::v3::node>;
    template<typename T>
    T extract_val(const node_view& in_node_view)
    {
        return in_node_view.template value<T>().value();
    }

    template<typename T>
    T extract_val(const toml::node& in_node)
    {
        return in_node.template value<T>().value();
    }

    
    template<typename T>
    T extract_val_or(const node_view& in_node_view, T in_default)
    {
        return in_node_view.template value<T>().value_or(in_default);
    }


    std::string extract_str_lowcase(const node_view& in_node_view)
    {
        return lower_case(in_node_view.template value<std::string>().value());   
    }

    std::string extract_str_lowcase(const toml::node& in_node)
    {
        return lower_case(in_node.template value<std::string>().value());   
    }


    template<typename T>
    T extract_enum_from_str(const node_view& in_node_view)
    {
        return convert_str_to_enum<T>(extract_str_lowcase(in_node_view));
    }

    template<typename T>
    T extract_enum_from_str(const toml::node& in_node)
    {
        return convert_str_to_enum<T>(extract_str_lowcase(in_node));
    }

    
    template<typename T>
    T extract_enum_from_str_or(const node_view& in_node_view, const T in_default)
    {
        return convert_str_to_enum<T>(extract_str_lowcase(in_node_view));
    }

    template<typename T>
    T extract_enum_from_str_or(const toml::node& in_node, const T in_default)
    {
        return convert_str_to_enum<T>(extract_str_lowcase(in_node));
    }


    template<typename T>
    std::vector<T> extract_array(const node_view& in_node_view)
    {
        if(auto* array_ptr = in_node_view.as_array())
        {
            std::vector<T> result;
            result.reserve(array_ptr->size());
            
            for(auto&& entry : *array_ptr)
            {
                result.push_back(extract_val<T>(entry));
            }

            return result;
        }

        return {};
    }


    template<typename T, unsigned_int U = u32>
    U extract_flags(const node_view& in_node_view)
    {
        U result = 0;
        if(toml::array* flag_array = in_node_view.as_array())
        {
            for(auto&& elem : *flag_array)
            {   
                result |= static_cast<U>(extract_enum_from_str<T>(elem));
            }
        }

        return result;
    }

}