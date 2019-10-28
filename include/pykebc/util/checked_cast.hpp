#pragma once

#include <stdexcept>


namespace pykebc::util
{

template <typename To, typename From, typename Exc = std::logic_error>
To* checked_cast(From* ptr, const char* message)
{
    auto cast_ptr = dynamic_cast<To*>(ptr);
    if (cast_ptr == nullptr) {
        throw Exc(message);
    }
    
    return cast_ptr;
}

}
