// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imanifestfactory.hpp"
#include "impl/common/objects/repositories/irepositoriesfactory.hpp"
#include "impl/common/objects/version/version.hpp"
#include "impl/manifest/objects/packages/ipackagesfactory.hpp"
#include "impl/manifest/operations/packagerepositorybinder/ipackagerepositorybinder.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

constexpr const char * MANIFEST_DOCUMENT_ID = "rpm-package-manifest";

inline const Version MANIFEST_DOCUMENT_VERSION = [] {
    Version version;
    version.set_major(0);
    version.set_minor(2);
    version.set_patch(3);
    return version;
}();

inline std::string manifest_document_version_string() {
    return std::to_string(MANIFEST_DOCUMENT_VERSION.get_major()) + "." +
           std::to_string(MANIFEST_DOCUMENT_VERSION.get_minor()) + "." +
           std::to_string(MANIFEST_DOCUMENT_VERSION.get_patch());
}

class ManifestFactory : public IManifestFactory {
public:
    ManifestFactory(
        std::shared_ptr<IPackagesFactory> packages_factory,
        std::shared_ptr<IRepositoriesFactory> repositories_factory,
        std::shared_ptr<IPackageRepositoryBinder> binder);

    virtual std::unique_ptr<IManifest> create() const override;

private:
    std::shared_ptr<IPackagesFactory> packages_factory;
    std::shared_ptr<IRepositoriesFactory> repositories_factory;
    std::shared_ptr<IPackageRepositoryBinder> binder;
};

}  // namespace libpkgmanifest::internal::manifest
