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
    using AttributeMap = std::unordered_map<std::string, Object*>;

    explicit Object() = default;
    Object(const Object& other) = delete;
    Object(Object&& other) = default;
    virtual ~Object() = default;

    size_t get_ref_count() const noexcept;
    void grab() noexcept;
    void drop() noexcept;

    Object* get_type() const noexcept;
    void set_type(Object* type) noexcept;

    virtual Object* get_attribute(const std::string& name) const;
    virtual void set_attribute(const std::string& name, Object* value);
    virtual bool has_attribute(const std::string& name) const noexcept;

private:
    size_t ref_count;
    Object* type;

    AttributeMap attributes;
};

} // namespace pykebc
