#pragma once

#include <pykebc/util/fits.hpp>

#include <stdexcept>


namespace pykebc::util
{

template <typename To, typename From, typename Exc = std::runtime_error>
constexpr To safe_uint_cast(From value, const char* message = "Erro in safe_uint_cast")
{
    static_assert(
        std::is_integral_v<To>
            && std::is_unsigned_v<To>
            && std::is_integral_v<From>
            && std::is_unsigned_v<From>,
        "Both To and From types must be unsigned integers"
    );

    if (!util::fits<To>(value)) {
        throw Exc(message);
    }

    return static_cast<To>(value);
}

}
