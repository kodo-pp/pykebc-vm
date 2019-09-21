#include <pykebc/object.hpp>


namespace pykebc
{

Object::Object(Object* type, bool always_reachable):
    type(type),
    always_reachable(always_reachable)
{ }

}
