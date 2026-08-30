#pragma once

#include <concepts>
namespace DSDR
{
    template<typename T>
    concept unsigned_int = std::unsigned_integral<T> && !std::same_as<T, bool>;
}