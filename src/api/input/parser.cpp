#include "input_impl.hpp"

#include "libpkgmanifest/common/exception.hpp"
#include "libpkgmanifest/input/parser.hpp"

#include "impl/input/operations/parser/parserfactory.hpp"

#include <format>

namespace libpkgmanifest::input {

using namespace libpkgmanifest::internal::input;

class Parser::Impl {
public:
    Impl() {
        parser = ParserFactory().create();
    }
private:
    friend Parser;
    std::unique_ptr<IParser> parser;
};

Parser::Parser() : p_impl(std::make_unique<Impl>()) {}

Parser::~Parser() = default;

Input Parser::parse(const std::string & path) const {
    Input input;

    try {
        input.p_impl->set(p_impl->parser->parse(path));
    } catch (const std::runtime_error & error) {
        throw ParserError(std::format("An error occurred during parsing of the input file at \"{}\": {}", path, error.what()));
    }

    return input;
}

Input Parser::parse_prototype(const std::string & path) const {
    Input input;

    try {
        input.p_impl->set(p_impl->parser->parse_from_prototype(path));
    } catch (const std::runtime_error & error) {
        throw ParserError(std::format("An error occurred during parsing of the input prototype file at \"{}\": {}", path, error.what()));
    }

    return input;
}

}