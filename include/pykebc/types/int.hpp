#pragma once

#include <pykebc/object.hpp>


namespace pykebc::types
{

class Int : public Object
{
public:
    explicit Int(long value) noexcept;
    
    long get_value() const noexcept;
    void set_value(long value) noexcept;

    Object* get_type
    static Object* get_type_object();

private:
    long value;
};

}
