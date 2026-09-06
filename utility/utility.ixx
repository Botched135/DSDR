export module utility;

import std;

export namespace DSDR
{
    // types 
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;


    // concepts 
    template<typename T>
    concept uint = std::unsigned_integral<T> && !std::same_as<T, bool>;


    // algorithms
    std::string lower_case(std::string&& in_str);
}