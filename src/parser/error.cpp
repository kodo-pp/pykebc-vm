#include <pykebc/parser.hpp>

namespace pykebc::parser
{

LoaderError(const std::string& message):
    std::runtime_error(message)
{ }

} // namespace pykebc::parser
