// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "manifest_impl.hpp"

#include "libpkgmanifest/common/exception.hpp"
#include "libpkgmanifest/manifest/parser.hpp"

#include "impl/manifest/operations/parser/parserfactory.hpp"

#include <format>

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

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