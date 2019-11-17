#include <pykebc/types/int.hpp>

#include <pykebc/builtin_objects.hpp>
#include <pykebc/object.hpp>
#include <pykebc/object_manager.hpp>
#include <pykebc/types/callables.hpp>


namespace pykebc::types
{

Int::Int(long value) noexcept:
    value(value)
{ }


long Int::get_value() const noexcept
{
    return value;
}


void Int::set_value(long value) noexcept
{
    this->value = value;
}


Object* Int::add(Object* rhs) const
{
    auto om = get_object_manager();
    if (rhs->is_instance(Int::get_type_object())) {
        // int + int
        auto int_rhs = checked_cast<Int>(rhs);
        return om.create_int(get_value() + int_rhs->get_value());
    if (rhs->is_instance(Float::get_type_object())) {
        // int + float
        auto int_rhs = checked_cast<Int>(rhs);
        return om.create_int(get_value() + int_rhs->get_value());
    } else {
        // int + unknown piece of shit
        raise_type_error("Only int of float can be added to int");
    }
}


Object* Int::bit_and(Object* rhs) const
{
    auto om = get_object_manager();
    if (rhs->is_instance(Int::get_type_object())) {
        // int & int
        auto int_rhs = checked_cast<Int>(rhs);
        return om.create_int(get_value() & int_rhs->get_value());
    } else {
        // int & other
        raise_type_error("Only int & int is defined");
    }
}


Object* Int::bit_invert() const
{
    auto om = get_object_manager();
    auto int_rhs = checked_cast<Int>(rhs);
    return om.create_int(~get_value());
}


Object* Int::bit_or(Object* rhs) const
{
    auto om = get_object_manager();
    if (rhs->is_instance(Int::get_type_object())) {
        // int | int
        auto int_rhs = checked_cast<Int>(rhs);
        return om.create_int(get_value() | int_rhs->get_value());
    } else {
        // int | other
        raise_type_error("Only int | int is defined");
    }
}


Object* Int::bit_xor(Object* rhs) const
{
    auto om = get_object_manager();
    if (rhs->is_instance(Int::get_type_object())) {
        // int ^ int
        auto int_rhs = checked_cast<Int>(rhs);
        return om.create_int(get_value() ^ int_rhs->get_value());
    } else {
        // int ^ other
        raise_type_error("Only int ^ int is defined");
    }
}


Object* Int::ceil() const
{
    return this;
}


Object* Int::floor() const
{
    return this;
}


Object* Int::floor_div(Object* rhs) const
{
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        auto om = get_object_manager();
        return om.create_int(get_value() / int_rhs.get_value());
    } else {
        // TODO: implement for float rhs
        raise_type_error("only int // int is implemented");
    }
}


Object* Int::format([[maybe_unused]] Object* format_string) const
{
    raise_not_implemented_error("int.__format__() is not implemented");
}


Object* Int::greater_or_equal(Object* rhs) const
{
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        auto om = get_object_manager();
        return make_bool(get_value() >= int_rhs.get_value());
    } else {
        // TODO: implement for float rhs
        raise_type_error("only int >= int is implemented");
    }
}


Object* Int::greater_than(Object* rhs) const
{
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        return make_bool(get_value() > int_rhs.get_value());
    } else {
        // TODO: implement for float rhs
        raise_type_error("only int > int is implemented");
    }
}


Object* Int::hash() const
{
    // TODO: use more adequate hash, such as xxhash, murmur or t1ha
    auto x = get_value();
    return get_object_manager().create_int((x * 17) ^ x);
}


Object* Int::index() const
{
    return this;
}


Object* Int::init(Object* value)
{
    // TODO: generalize
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        set_value(int_rhs->get_value());
        return get_none_object();
    }
    
    raise_type_error("only int(int) is implemented");
}


Object* Int::less_or_equal(Object* rhs)
{
    // TODO: generalize
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        return make_bool(get_value() <= int_rhs.get_value());
    }
    raise_type_error("only int <= int is implemented");
}


Object* Int::less_than(Object* rhs)
{
    // TODO: generalize
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        return make_bool(get_value() < int_rhs.get_value());
    }
    raise_type_error("only int < int is implemented");
}


Object* Int::lshift(Object* rhs)
{
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        auto om = get_object_manager();
        return om.create_int(get_value() << int_rhs.get_value());
    }
    raise_type_error("invalid '<<' operation: only int << int is defined");
}


Object* Int::mod(Object* rhs)
{
    // TODO: float rhs
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        auto om = get_object_manager();
        return om.create_int(get_value() % int_rhs.get_value());
    }
    raise_type_error("only int % int is implemented");
}


Object* Int::mult(Object* rhs)
{
    // TODO: float rhs
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        auto om = get_object_manager();
        return om.create_int(get_value() * int_rhs.get_value());
    }
    raise_type_error("only int * int is implemented");
}


Object* Int::negate()
{
    auto om = get_object_manager();
    return om.create_int(-get_value());
}


Object* Int::not_equal(Object* rhs)
{
    // TODO: generalize
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        return make_bool(get_value() != int_rhs.get_value());
    }
    raise_type_error("only int != int is implemented");
}


Object* Int::power([[maybe_unused]] Object* rhs)
{
    // TODO: implement
    raise_not_implemented_error("int.__pow__() is not implemented");
}


Object* Int::repr()
{
    // TODO: implement
    raise_not_implemented_error("int.__repr__() is not implemented");
}


Object* Int::round()
{
    return this;
}


Object* Int::str()
{
    // TODO: implement
    raise_not_implemented_error("int.__str__() is not implemented");
}


Object* Int::sub(Object* rhs)
{
    // TODO: float rhs
    if (rhs->is_instance(Int::get_type_object())) {
        auto int_rhs = checked_cast<Int>(rhs);
        auto om = get_object_manager();
        return om.create_int(get_value() - int_rhs.get_value());
    }
    raise_type_error("only int - int is implemented");
}


Object* Int::to_bool()
{
    return make_bool(get_value() != 0);
}


Object* Int::to_float()
{
    // TODO: implement
    raise_not_implemented_error("int.__float__() is not implemented");
}


Object* Int::to_int()
{
    return this;
}


Object* Int::true_div(Object* rhs)
{
    // TODO: implement
    raise_not_implemented_error("int.__truediv__() is not implemented");
}


Object* Int::trunc()
{
    return this;
}


#define DECLARE_METHOD_1(py_method_name, cpp_method_name) \
    obj.set_attribute( \
        #py_method_name, \
        om.create_native_function( \
            [](const ArgumentList& args) { \
                return checked_cast<Int>(args.args.at(0))->cpp_method_name(args.args.at(1)); \
            }, \
            ArgumentListDescription().with_pos_only_arg("self").with_pos_only_arg("rhs") \
        ) \
    )


#define DECLARE_METHOD_0(py_method_name, cpp_method_name) \
    obj.set_attribute( \
        #py_method_name, \
        om.create_native_function( \
            [](const ArgumentList& args) { \
                return checked_cast<Int>(args.args.at(0))->cpp_method_name(); \
            }, \
            ArgumentListDescription().with_pos_only_arg("self") \
        ) \
    )


Object* Int::get_type_object()
{
    // TODO: implement locking for synchronization
    static bool constructed = false;
    auto om = get_object_manager();
    static Object* obj = om.create_object(get_bto_type());
    if (constructed) {
        return obj;
    }

    DECLARE_METHOD_1(__add__,       add);
    DECLARE_METHOD_1(__and__,       bit_and);
    DECLARE_METHOD_1(__or__,        bit_or);
    DECLARE_METHOD_1(__xor__,       bit_xor);
    DECLARE_METHOD_1(__floordiv__,  floor_div);
    DECLARE_METHOD_1(__format__,    format);
    DECLARE_METHOD_1(__ge__,        greater_or_equal);
    DECLARE_METHOD_1(__gt__,        greater_than);
    DECLARE_METHOD_1(__le__,        less_or_equal);
    DECLARE_METHOD_1(__lt__,        less_than);
    DECLARE_METHOD_1(__lshift__,    lshift);
    DECLARE_METHOD_1(__mod__,       mod);
    DECLARE_METHOD_1(__mul__,       mult);
    DECLARE_METHOD_1(__ne__,        not_equal);
    DECLARE_METHOD_1(__pow__,       power);
    DECLARE_METHOD_1(__sub__,       sub);
    DECLARE_METHOD_1(__truediv__,   true_div);

    DECLARE_METHOD_0(__invert__,    bit_invert);
    DECLARE_METHOD_0(__ceil__,      ceil);
    DECLARE_METHOD_0(__floor__,     floor);
    DECLARE_METHOD_0(__hash__,      hash);
    DECLARE_METHOD_0(__index__,     index);
    DECLARE_METHOD_0(__neg__,       negate);
    DECLARE_METHOD_0(__repr__,      repr);
    DECLARE_METHOD_0(__round__,     round);
    DECLARE_METHOD_0(__str__,       str);
    DECLARE_METHOD_0(__bool__,      to_bool);
    DECLARE_METHOD_0(__float__,     to_float);
    DECLARE_METHOD_0(__int__,       to_int);
    DECLARE_METHOD_0(__trunc__,     trunc);

    return obj;
}

}
