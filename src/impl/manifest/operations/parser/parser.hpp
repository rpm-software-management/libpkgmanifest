#pragma once

#include "iparser.hpp"

#include "impl/common/yaml/iyamlparser.hpp"
#include "impl/manifest/objects/manifest/imanifestparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class Parser : public IParser {
public:
    Parser(
        std::unique_ptr<IYamlParser> yaml_parser,
        std::unique_ptr<IManifestParser> manifest_parser);

    virtual std::unique_ptr<IManifest> parse(const std::string & path) const override;

private:
    std::unique_ptr<IYamlParser> yaml_parser;
    std::unique_ptr<IManifestParser> manifest_parser;
};

}