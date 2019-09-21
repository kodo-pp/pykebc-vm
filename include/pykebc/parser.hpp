#pragma once

#include <stdexcept>


namespace pykebc::parser
{

/// An exception thrown when the Pyke bytecode cannot be parsed
class Error : public std::runtime_error
{
public:
    LoaderError(const std::string& message):
        std::runtime_error(message)
    { }
};



} // namespace pykebc::parser
