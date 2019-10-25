#pragma once

#include <pykebc/object.hpp>


namespace pykebc::types
{

enum class BuiltinType
{
    //py_bool,
    //py_bytes,
    //py_complex,
    //py_dict,
    //py_float,
    //py_function,
    py_int,
    //py_list,
    //py_module,
    py_none_type,
    //py_set,
    //py_str,
    //py_type,
};


Object* get_builtin_type_object(BuiltinType type);

}
