#pragma once

#include <type_traits>


namespace pykebc::util
{

template <typename To, typename From>
constexpr bool fits(From value)
{
    static_assert(
        std::is_integral_v<To>
            && std::is_unsigned_v<To>
            && std::is_integral_v<From>
            && std::is_unsigned_v<From>,
        "Both To and From types must be unsigned integers"
    );

    return From(To(value)) == value;
}

}
