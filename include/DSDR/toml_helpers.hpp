#pragma once 
#include <toml++/toml.hpp>
namespace DSDR
{
    using node_view = toml::v3::node_view<toml::v3::node>;
    template<typename T>
    T extract_val(const node_view& in_node_view)
    {
        return in_node_view.template value<T>().value();
    }

    template<typename T>
    T extract_val_or(const node_view& in_node_view, T in_default)
    {
        return in_node_view.template value<T>().value_or(in_default);
    }
}