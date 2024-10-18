#include "parser.hpp"

namespace libpkgmanifest::internal {

Parser::Parser(
    std::unique_ptr<IYamlParser> yaml_parser,
    std::unique_ptr<IInputParser> input_parser,
    std::unique_ptr<IManifestParser> manifest_parser,
    std::unique_ptr<IPrototypeInFileConverter> prototype_converter)
    : yaml_parser(std::move(yaml_parser))
    , input_parser(std::move(input_parser))
    , manifest_parser(std::move(manifest_parser))
    , prototype_converter(std::move(prototype_converter)) {}

std::unique_ptr<IInput> Parser::parse_input(const std::string & path) const {
    auto node = yaml_parser->from_file(path);
    auto input = input_parser->parse(*node);
    return input;
}

std::unique_ptr<IInput> Parser::parse_input_from_prototype(const std::string & path) const {
    auto node = prototype_converter->convert(*yaml_parser->from_file(path));
    auto input = input_parser->parse(*node);
    return input;
}

std::unique_ptr<IManifest> Parser::parse_manifest(const std::string & path) const {
    auto node = yaml_parser->from_file(path);
    auto manifest = manifest_parser->parse(*node);
    return manifest;
}

}