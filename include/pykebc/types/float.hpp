#pragma once

#include <pykebc/object.hpp>


namespace pykebc::types
{

class Float : public Object
{
public:
    explicit Float(double value) noexcept;
    
    double get_value() const noexcept;
    void set_value(double value) noexcept;

    static Object* get_type_object();

private:
    double value;
};

}
