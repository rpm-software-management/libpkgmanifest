#pragma once

#include "imanifestfactory.hpp"
#include "imanifestparser.hpp"

#include "libpkgmanifest/objects/packages/ipackagesparser.hpp"
#include "libpkgmanifest/objects/repositories/irepositoriesparser.hpp"
#include "libpkgmanifest/objects/version/iversionparser.hpp"
#include "libpkgmanifest/operations/ipackagerepositorybinder.hpp"

namespace libpkgmanifest::internal {

class ManifestParser : public IManifestParser {
public:
    ManifestParser(
        std::unique_ptr<IManifestFactory> manifest_factory,
        std::unique_ptr<IPackagesParser> packages_parser,
        std::unique_ptr<IRepositoriesParser> repositories_parser,
        std::unique_ptr<IVersionParser> version_parser,
        std::shared_ptr<IPackageRepositoryBinder> binder);

    virtual std::unique_ptr<IManifest> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IManifestFactory> manifest_factory;
    std::unique_ptr<IPackagesParser> packages_parser;
    std::unique_ptr<IRepositoriesParser> repositories_parser;
    std::unique_ptr<IVersionParser> version_parser;
    std::shared_ptr<IPackageRepositoryBinder> binder;
};

}