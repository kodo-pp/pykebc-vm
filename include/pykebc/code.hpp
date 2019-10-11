#pragma once

#include <pykebc/object.hpp>

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>


namespace pykebc::code
{


struct Code
{
    std::vector<uint32_t> instructions;
    std::vector<Object*> constants;
};


class Module : public Object
{
public:
    ModuleCode(
        Code code,
        bool always_reachable = false
    );

    Object* run();

private:
    Code code;
};


struct ArgumentListDescription
{
    std::vector<std::string> args;
    std::vector<std::string> kw_only_args;
    std::optional<std::string> star_arg;
    std::optional<std::string> star_kwarg;
};


struct ArgumentList
{
    std::vector<Object*> args;
    std::unordered_map<std::string, Object*> kwargs;
};


class FunctionLike : public Object
{
public:
    virtual Object* run(const ArgumentList& args) = 0;
};


class Function : public FunctionLike
{
public:
    Function(
        Code code,
        ArgumentListDescription args,
        bool always_reachable = false
    );

    Object* run(const ArgumentList& args) override;
};


class Class : public FunctionLike
{
public:
    Class(
        Code code,
        ArgumentListDescription args,
        bool always_reachable = false
    );

    Object* run(const ArgumentList& args) override;
};


} // namespace pykebc
