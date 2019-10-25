#pragma once

#include <pykebc/object.hpp>
#include <pykebc/types/callables.hpp>

#include <unordered_set>


namespace pykebc
{

class ObjectManager
{
public:
    ObjectManager() = default;
    ObjectManager(const ObjectManager& other) = delete;

    ~ObjectManager();

    Object* create_object(Object* type);
    Object* create_native_function(const types::NativeFunction::FunctionType& func);

private:
    std::unordered_set<Object*> objects;
};


ObjectManager& get_object_manager();

}
