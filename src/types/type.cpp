#include <pykebc/types/type.hpp>


namespace pykebc::types
{

namespace
{
    using code::ArgumentList;
    using code::ArgumentListDescription;

    Object* get_bto_none_type()
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
                [](const ArgumentList& args) {
                    return args.args.at(0); // args.args[0] == self == None
                },
                ArgumentListDescription().with_pos_only_args({"self"})
            )
        );

        obj.set_attribute(
            "__bool__",
            om.create_native_function(
                [obj]([[maybe_unused]] const ArgumentList& args) {
                    return get_false_object();
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
    }
}

}
