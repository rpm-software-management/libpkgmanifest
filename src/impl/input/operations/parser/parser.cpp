// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "parser.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

Parser::Parser(
    std::unique_ptr<IYamlParser> yaml_parser,
    std::unique_ptr<IInputParser> input_parser,
    std::unique_ptr<IPrototypeFileConverter> prototype_converter)
    : yaml_parser(std::move(yaml_parser))
    , input_parser(std::move(input_parser))
    , prototype_converter(std::move(prototype_converter)) {}

std::unique_ptr<IInput> Parser::parse(const std::string & path) const {
    auto node = yaml_parser->from_file(path);
    auto input = input_parser->parse(*node);
    return input;
}

std::unique_ptr<IInput> Parser::parse_from_prototype(const std::string & path) const {
    auto node = prototype_converter->convert(*yaml_parser->from_file(path));
    auto input = input_parser->parse(*node);
    return input;
}

}