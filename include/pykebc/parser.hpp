#pragma once

#include <pykebc/code.hpp>
#include <pykebc/object.hpp>

#include <stdexcept>
#include <vector>

#include <libbinary_format/data_reader.hpp>


namespace pykebc::parser
{

/// An exception thrown when the Pyke bytecode cannot be parsed
class Error : public std::runtime_error
{
public:
    Error(const std::string& message);
};


class Parser
{
public:
    explicit Parser(std::vector<uint8_t> bytecode);
    Parser(const Parser& other) = delete;

    Object* read_object();
    Object* read_bytes();
    Object* read_int();
    Object* read_float();
    Object* read_complex();
    Object* read_none();
    Object* read_utf8_str();
    Object* read_code();
    Object* read_false();
    Object* read_true();

private:
    std::vector<uint8_t> bytecode;
    libbinary_format::DataReader data_reader;
    size_t offset = 0;
};

} // namespace pykebc::parser
