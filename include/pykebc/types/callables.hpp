#pragma once

#include <pykebc/object.hpp>

#include <optional>
#include <string>
#include <vector>


namespace pykebc::types
{

struct ArgumentListDescription
{
    struct Argument
    {
        std::string name;
        std::optional<Object*> default_value;
    }

    ArgumentListDescription& with_arg(std::string arg);
    ArgumentListDescription& with_arg(std::string arg, Object* default_value);

    ArgumentListDescription& with_pos_only_arg(std::string arg);
    ArgumentListDescription& with_pos_only_arg(std::string arg, Object* default_value);

    ArgumentListDescription& with_kw_only_arg(std::string arg);
    ArgumentListDescription& with_kw_only_arg(std::string arg, Object* default_value);

    ArgumentListDescription& with_star_arg(std::string star_arg);
    ArgumentListDescription& with_star_kwarg(std::string star_kwarg);

    std::vector<Argument> args;
    std::vector<Argument> pos_only_args;
    std::vector<Argument> kw_only_args;
    std::optional<Argument> star_arg;
    std::optional<Argument> star_kwarg;
};


struct ArgumentList
{
    std::vector<Object*> args;
    std::unordered_map<std::string, Object*> kwargs;
};


class Callable : public Object
{
public:
    explicit Callable(ArgumentListDescription args_description);

    virtual Object* call(const ArgumentList& args) = 0;

protected:
    ArgumentListDescription args_description;
};


class PythonFunction : public Callable
{
public:
    explicit PythonFunction(Code code, ArgumentListDescription args_description);

    Object* call(const ArgumentList& args);

private:
    Code code;
};


class NativeFunction : public Callable
{
public:
    using FunctionType = std::function<Object*(const ArgumentList&)>;

    explicit PythonFunction(FunctionType native_code, ArgumentListDescription args_description);

    Object* call(const ArgumentList& args);

private:
    FunctionType native_code;
};

}
