#pragma once

#include "imanifestfactory.hpp"
#include "imanifestparser.hpp"

#include "libpkgmanifest/objects/packages/ipackagesparser.hpp"
#include "libpkgmanifest/objects/version/iversionparser.hpp"

namespace libpkgmanifest::internal {

class ManifestParser : public IManifestParser {
public:
    ManifestParser(
        std::unique_ptr<IManifestFactory> manifest_factory,
        std::unique_ptr<IPackagesParser> packages_parser,
        std::unique_ptr<IVersionParser> version_parser);

    virtual std::unique_ptr<IManifest> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IManifestFactory> manifest_factory;
    std::unique_ptr<IPackagesParser> packages_parser;
    std::unique_ptr<IVersionParser> version_parser;
};

}