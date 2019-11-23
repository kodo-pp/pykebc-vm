#include <pyekbc/util/fits.hpp>
#include <pykebc/parser.hpp>

#include <string_view>


namespace pykebc::parser
{

namespace
{
    template <typename Raw, typename Exc = Error>
    size_t read_length(libbinary_format::DataReader& data_reader)
    {
        auto raw = data_reader.read_uint<Raw>();
        return util::safe_uint_cast<size_t, Raw, Exc>(
            raw,
            "Length is too large; it does not fit into size_t"
        );
    }
}


Parser::Parser(std::vector<uint8_t> bytecode):
    bytecode(std::move(bytecode)),
    data_reader(
        std::string_view(
            static_cast<const char*>(bytecode.data()),
            bytecode.size()
        )
    )
{ }


Object* Parser::read_object()
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

Object* Parser::read_int()
{
    size_t num_bytes = read_length<uint64_t>(data_reader);
    std::vector<uint8_t> buf(num_bytes);
    data_reader.read_bytes(num_bytes, buf.data());

    auto& om = get_object_manager();
    return om.create_int(std::move(buf));
}


Object* Parser::read_none()
{
    return none_object;
}


Object* Parser::read_bytes()
{
    size_t num_bytes = read_length<uint64_t>(data_reader);
    std::vector<uint8_t> data(num_bytes);
    data_reader.read_bytes(num_bytes, data.data());

    auto& om = get_object_manager();
    return om.create_bytes(std::move(buf));
}


Object* Parser::read_false()
{
    return false_object;
}


Object* Parser::read_true()
{
    return true_object;
}


Object* Parser::read_code()
{
    size_t total_length = read_length(data_reader);
    size_t remaining_bytes_before_read = data_reader.get_number_of_bytes_left();

    uint8_t code_type = data_reader.read_uint<uint8_t>();

    size_t num_constants = read_length(data_reader);
    std::vector<Object*> constants;
    constants.reserve(num_constants);
    for (size_t i = 0; i < num_constants; ++i) {
        constants.push_back(read_object());
    }

    size_t num_instructions = read_length(data_reader);
    std::vector<uint32_t> instructions;
    instructions.reserve(num_instructions);
    for (size_t i = 0; i < num_instructions; ++i) {
        instructions.push_back(data_reader.read_uint<uint32_t>());
    }

    auto& om = get_object_manager();
    switch(code_type) {
        case 0: {
            // module
            return om.create_module(std::move(constants), std::move(instructions));
        }
        case 1: {
            // function
            return om.create_function(std::move(constants), std::move(instructions));
        }
        case 2: {
            // class
            return om.create_class(std::move(constants), std::move(instructions));
        }
        default: {
            throw Error(
                "Invalid code type: "
                    + std::to_string(static_cast<unsigned int>(code_type))
            );
        }
    }
}

} // namespace pykebc::parser
