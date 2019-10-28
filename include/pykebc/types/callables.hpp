#pragma once

#include <pykebc/object.hpp>

#include <optional>
#include <string>
#include <vector>


namespace pykebc::types
{

struct ArgumentListDescription
{
    ArgumentListDescription& with_args(std::vector<std::string> args);
    ArgumentListDescription& with_pos_only_args(std::vector<std::string> args);
    ArgumentListDescription& with_kw_only_args(std::vector<std::string> args);
    ArgumentListDescription& with_star_arg(std::string star_arg);
    ArgumentListDescription& with_star_kwarg(std::string star_kwarg);

    std::vector<std::string> args;
    std::vector<std::string> pos_only_args;
    std::vector<std::string> kw_only_args;
    std::optional<std::string> star_arg;
    std::optional<std::string> star_kwarg;
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
