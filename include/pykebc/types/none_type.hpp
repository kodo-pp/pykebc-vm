#pragma once

#include <pykebc/object.hpp>


namespace pykebc::types
{

class NoneType : public Object
{
public:
    explicit NoneType() = default;

    static Object* get_type_object();
};

}
