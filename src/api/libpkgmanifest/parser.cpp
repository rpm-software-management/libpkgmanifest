#include "manifest_impl.hpp"

#include "libpkgmanifest/exception.hpp"
#include "libpkgmanifest/parser.hpp"

#include "libpkgmanifest/operations/parserfactory.hpp"

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

Manifest Parser::parse(const std::string & path) const {
    Manifest manifest;

    try {
        manifest.p_impl->set(p_impl->parser->parse(path));
    } catch (const std::runtime_error & error) {
        throw ParserError(std::format("An error occurred during parsing of the manifest file at \"{}\": {}", path, error.what()));
    }

    return manifest;
}

}