#pragma once

#include <pykebc/object.hpp>


namespace pykebc::types
{

class Bool : public Object
{
public:
    explicit Bool(bool value) noexcept;
    
    bool get_value() const noexcept;

    static Object* get_type_object();

private:
    bool value;
};

}
