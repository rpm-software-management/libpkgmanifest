// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imanifestfactory.hpp"
#include "imanifestparser.hpp"

#include "impl/common/objects/repositories/irepositoriesparser.hpp"
#include "impl/common/objects/version/iversionparser.hpp"
#include "impl/manifest/objects/packages/ipackagesparser.hpp"
#include "impl/manifest/operations/packagerepositorybinder/ipackagerepositorybinder.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class ManifestParser : public IManifestParser {
public:
    ManifestParser(
        std::unique_ptr<IManifestFactory> manifest_factory,
        std::unique_ptr<IPackagesParser> packages_parser,
        std::shared_ptr<IRepositoriesParser> repositories_parser,
        std::shared_ptr<IVersionParser> version_parser,
        std::shared_ptr<IPackageRepositoryBinder> binder);

    virtual std::unique_ptr<IManifest> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IManifestFactory> manifest_factory;
    std::unique_ptr<IPackagesParser> packages_parser;
    std::shared_ptr<IRepositoriesParser> repositories_parser;
    std::shared_ptr<IVersionParser> version_parser;
    std::shared_ptr<IPackageRepositoryBinder> binder;
};

}