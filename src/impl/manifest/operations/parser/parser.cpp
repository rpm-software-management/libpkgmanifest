// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "parser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

Parser::Parser(
    std::unique_ptr<IYamlParser> yaml_parser,
    std::unique_ptr<IManifestParser> manifest_parser)
    : yaml_parser(std::move(yaml_parser))
    , manifest_parser(std::move(manifest_parser)) {}

std::unique_ptr<IManifest> Parser::parse(const std::string & path) const {
    auto node = yaml_parser->from_file(path);
    auto manifest = manifest_parser->parse(*node);
    return manifest;
}

}