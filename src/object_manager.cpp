#include <pykebc/object_manager.hpp>
#include <pykebc/object.hpp>
#include <pykebc/types/int.hpp>
#include <pykebc/types/none_type.hpp>
#include <pykebc/types/bool.hpp>
#include <pykebc/types/callables.hpp>


namespace pykebc
{

ObjectManager::~ObjectManager()
{
    // TODO: delete all remaining objects
}


ObjectManager::create_object(Object* type)
{
}

}
