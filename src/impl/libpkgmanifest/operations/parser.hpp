#pragma once

#include "iparser.hpp"

#include "libpkgmanifest/objects/manifest/imanifestparser.hpp"
#include "libpkgmanifest/yaml/iyamlparser.hpp"

namespace libpkgmanifest::internal {

class Parser : public IParser {
public:
    Parser(std::unique_ptr<IYamlParser> yaml_parser, std::unique_ptr<IManifestParser> manifest_parser);

    virtual std::unique_ptr<IManifest> parse(const std::string & path) const override;

private:
    std::unique_ptr<IYamlParser> yaml_parser;
    std::unique_ptr<IManifestParser> manifest_parser;
};

}