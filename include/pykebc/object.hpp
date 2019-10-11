#pragma once

#include <pykebc/reference_holder.hpp>

#include <memory>
#include <string>
#include <unordered_map>


namespace pykebc
{

class Object
{
public:
    Object(Object* type, bool always_reachable = false);
    Object(const Object& other) = delete;
    Object(Object&& other) = default;
    virtual ~Object() = default;

    size_t ref_count;
    Object* type;
    bool always_reachable;

    std::unordered_map<std::string, Object*> attributes;
};

} // namespace pykebc
