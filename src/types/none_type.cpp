#include <pykebc/types/none_type.hpp>

#include <pykebc/builtin_objects.hpp>
#include <pykebc/object.hpp>
#include <pykebc/object_manager.hpp>
#include <pykebc/types/callables.hpp>


namespace pykebc::types
{

using namespace builtin_objects;

Object* NoneType::get_type_object()
{
    // TODO: implement locking for synchronization
    static bool constructed = false;
    auto& om = get_object_manager();
    static Object* obj = om.create_object(get_bto_type());
    if (constructed) {
        return obj;
    }

    obj.set_attribute(
        "__init__",
        om.create_native_function(
            [](const ArgumentList& args) {
                // We want not to return anything, which is equivalent to returning None.
                // We cannot use builtin_objects::get_none_object() here because it will
                // cause infinite mutual recursion. However, as this is the `__init__` method,
                // `self` is passed to it as an argument, so we can return `self`.
                return args.args.at(0); // args.args[0] == self == None
            },
            ArgumentListDescription().with_pos_only_arg("self")
        )
    );

    obj.set_attribute(
        "__bool__",
        om.create_native_function(
            [obj]([[maybe_unused]] const ArgumentList& args) {
                return get_false_object();
            },
            ArgumentListDescription().with_pos_only_arg("self")
        )
    );

    auto repr_function = om.create_native_function(
        [obj](const ArgumentList& args) {
            return om.create_str("None");
        },
        ArgumentListDescription().with_pos_only_arg("self")
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
