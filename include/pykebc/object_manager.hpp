#pragma once

#include <pykebc/object.hpp>
#include <pykebc/types/callables.hpp>
#include <pykebc/util/unicode_string.hpp>

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
    Object* create_str(util::UnicodeString&& str);
    Object* create_str(const char* c_str);
    Object* create_type_error(Object* arg);
    Object* create_int(std::vector<uint8_t>&& buf);
    Object* create_bytes(std::vector<uint8_t>&& buf);
    Object* create_module(std::vector<Object*>&& constants, std::vector<uint32_t>&& instructions);
    Object* create_function(std::vector<Object*>&& constants, std::vector<uint32_t>&& instructions);
    Object* create_class(std::vector<Object*>&& constants, std::vector<uint32_t>&& instructions);

private:
    std::unordered_set<Object*> objects;
};


ObjectManager& get_object_manager();

}
