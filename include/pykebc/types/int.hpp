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

    static Object* get_type_object();

    // Holy shit! I've never even thought Python had so many methods
    Object* add(Object* rhs)                    const;  // __add__
    Object* bit_and(Object* rhs)                const;  // __and__
    Object* bit_invert()                        const;  // __invert__
    Object* bit_or(Object* rhs)                 const;  // __or__
    Object* bit_xor(Object* rhs)                const;  // __xor__
    Object* ceil()                              const;  // __ceil__
    Object* floor()                             const;  // __floor__
    Object* floor_div(Object* rhs)              const;  // __floordiv__
    Object* format(Object* format_string)       const;  // __format__
    Object* greater_or_equal(Object* rhs)       const;  // __ge__
    Object* greater_than(Object* rhs)           const;  // __gt__
    Object* hash()                              const;  // __hash__
    Object* index()                             const;  // __index__
    Object* init(Object* value);                        // __init__
    Object* less_or_equal(Object* rhs)          const;  // __le__
    Object* less_than(Object* rhs)              const;  // __lt__
    Object* lshift(Object* rhs)                 const;  // __lshift__
    Object* mod(Object* rhs)                    const;  // __mod__
    Object* mult(Object* rhs)                   const;  // __mul__
    Object* negate()                            const;  // __neg__
    Object* not_equal(Object* rhs)              const;  // __ne__
    Object* power(Object* rhs)                  const;  // __pow__
    Object* power(Object* rhs)                  const;  // __pow__
    Object* repr()                              const;  // __repr__
    Object* round()                             const;  // __round__
    Object* str()                               const;  // __str__
    Object* sub(Object* rhs)                    const;  // __sub__
    Object* to_bool()                           const;  // __bool__
    Object* to_float()                          const;  // __float__
    Object* to_int()                            const;  // __int__
    Object* true_div(Object* rhs)               const;  // __truediv__
    Object* trunc(Object* rhs)                  const;  // __trunc__

private:
    long value;
};

}
