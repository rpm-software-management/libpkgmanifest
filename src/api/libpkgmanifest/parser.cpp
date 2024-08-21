#include "manifest_impl.hpp"

#include "libpkgmanifest/parser.hpp"

#include "libpkgmanifest/operations/parserfactory.hpp"

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
    manifest.p_impl->set(p_impl->parser->parse(path));
    return manifest;
}

}