#include <pykebc/builtin_objects.hpp>
#include <pykebc/object_manager.hpp>
#include <pykebc/types/type.hpp>
#include <pykebc/util/checked_cast.hpp>


namespace pykebc::types
{

namespace
{
    using code::ArgumentList;
    using code::ArgumentListDescription;
    using namespace builtin_objects;


    Object* get_bto_int()
    {
        // TODO: implement locking for synchronization
        static bool constructed = false;
        auto om = get_object_manager();
        static Object* obj = om.create_object(get_bto_type());
        if (constructed) {
            return obj;
        }

        obj.set_attribute(
            "__init__",
            om.create_native_function(
                [obj](const ArgumentList& args) {
                    auto self = args.args.at(0);
                    auto value = args.args.at(1);
                    auto int_self = util::checked_cast<Int*>(self);

                    if (value->is_instance(obj)) {
                        // value is int
                        auto int_value = util::checked_cast<Int*>(value);
                        int_self->set_value(int_value->get_value());
                    } else {
                        auto om = get_object_manager();
                        auto type_error = om.create_type_error(
                            om.create_str(
                                "int() expected a string, bytes, float or int"
                            )
                        );
                        vm::get_running_vm().raise(type_error);
                    }

                    return get_none_object();
                },
                ArgumentListDescription().with_pos_only_args({"self", "value"})
            )
        );

        obj.set_attribute(
            "__bool__",
            om.create_native_function(
                [obj](const ArgumentList& args) {
                    auto self = args.args.at(0);
                    auto int_self = util::checked_cast<Int*>(self);
                    
                    auto is_zero = (int_self->get_value() == 0);
                    if (is_zero) {
                        return get_false_object();
                    } else {
                        return get_true_object();
                    }
                },
                ArgumentListDescription().with_pos_only_args({"self"})
            )
        );

        auto repr_function = om.create_native_function(
            [obj](const ArgumentList& args) {
                return om.create_str("None");
            },
            ArgumentListDescription().with_pos_only_args({"self"})
        );

        obj.set_attribute(
            "__str__",
            repr_function
        );

        obj.set_attribute(
            "__repr__",
            repr_function
        );

        constructed = true;
        return obj;
    }
}


Object* get_builtin_type_object(BuiltinType type)
{
    switch (type) {
        case BuiltinType::py_none_type:
            return get_bto_none_type();
        case BuiltinType::py_int:
            return get_bto_int();
    }
}

}
