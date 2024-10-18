#include "input_impl.hpp"
#include "manifest_impl.hpp"

#include "libpkgmanifest/common/exception.hpp"
#include "libpkgmanifest/operations/parser.hpp"

#include "impl/libpkgmanifest/operations/parserfactory.hpp"

#include <format>

namespace libpkgmanifest {

class Parser::Impl {
public:
    Impl() {
        parser = internal::ParserFactory().create();
    }
private:
    friend Parser;
    std::unique_ptr<internal::IParser> parser;
};

Parser::Parser() : p_impl(std::make_unique<Impl>()) {}

Parser::~Parser() = default;

Manifest Parser::parse_manifest(const std::string & path) const {
    Manifest manifest;

    try {
        manifest.p_impl->set(p_impl->parser->parse_manifest(path));
    } catch (const std::runtime_error & error) {
        throw ParserError(std::format("An error occurred during parsing of the manifest file at \"{}\": {}", path, error.what()));
    }

    return manifest;
}

Input Parser::parse_input(const std::string & path) const {
    Input input;

    try {
        input.p_impl->set(p_impl->parser->parse_input(path));
    } catch (const std::runtime_error & error) {
        throw ParserError(std::format("An error occurred during parsing of the input file at \"{}\": {}", path, error.what()));
    }

    return input;
}

Input Parser::parse_prototype_input(const std::string & path) const {
    Input input;

    try {
        input.p_impl->set(p_impl->parser->parse_input_from_prototype(path));
    } catch (const std::runtime_error & error) {
        throw ParserError(std::format("An error occurred during parsing of the input prototype file at \"{}\": {}", path, error.what()));
    }

    return input;
}

}