#include <pykebc/parser.hpp>

#include <string_view>


namespace pykebc::parser
{

Parser::Parser(std::vector<uint8_t> bytecode):
    bytecode(std::move(bytecode)),
    data_reader(
        std::string_view(
            static_cast<const char*>(bytecode.data()),
            bytecode.size()
        )
    )
{ }

Object* read_object()
{
    char type_byte = 0;
    data_reader.read_bytes(1, &type_byte);

    switch (type_byte) {
        case 'i':
            return read_int();
        case 'f':
            return read_float();
        case 'c':
            return read_complex();
        case 'n':
            return read_none();
        case 'b':
            return read_bytes();
        case 'u':
            return read_utf8_str();
        case '#':
            return read_code();
        case '0':
            return read_false();
        case '1':
            return read_true();
        default:
            throw Error(std::string("Unknown object type character: '") + type_byte + "'");
    }
}

Object* read_int()

} // namespace pykebc::parser
