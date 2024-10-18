#pragma once

#include "iparser.hpp"

#include "impl/libpkgmanifest/objects/input/iinputparser.hpp"
#include "impl/libpkgmanifest/objects/manifest/imanifestparser.hpp"
#include "impl/libpkgmanifest/operations/iprototypeinfileconverter.hpp"
#include "impl/libpkgmanifest/yaml/iyamlparser.hpp"

namespace libpkgmanifest::internal {

class Parser : public IParser {
public:
    Parser(
        std::unique_ptr<IYamlParser> yaml_parser,
        std::unique_ptr<IInputParser> input_parser,
        std::unique_ptr<IManifestParser> manifest_parser,
        std::unique_ptr<IPrototypeInFileConverter> prototype_converter);

    virtual std::unique_ptr<IInput> parse_input(const std::string & path) const override;
    virtual std::unique_ptr<IInput> parse_input_from_prototype(const std::string & path) const override;
    virtual std::unique_ptr<IManifest> parse_manifest(const std::string & path) const override;

private:
    std::unique_ptr<IYamlParser> yaml_parser;
    std::unique_ptr<IInputParser> input_parser;
    std::unique_ptr<IManifestParser> manifest_parser;
    std::unique_ptr<IPrototypeInFileConverter> prototype_converter;
};

}