#pragma once

#include <pykebc/object.hpp>

#include <cstdint>
#include <vector>


namespace pykebc::code
{

struct Code
{
    std::vector<uint32_t> instructions;
    std::vector<Object*> constants;
};

} // namespace pykebc
