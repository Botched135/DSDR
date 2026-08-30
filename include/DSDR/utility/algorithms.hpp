#pragma once

#include <string>
#include <algorithm>
#include <cctype>

namespace DSDR
{
    std::string lower_case(std::string&& in_str)
    {
        std::ranges::transform(in_str, in_str.begin(), [](auto c)
        {
            return std::tolower(c);
        });
        return in_str;
    }
}