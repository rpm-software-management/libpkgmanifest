#pragma once

#include "imanifestfactory.hpp"

#include "impl/libpkgmanifest/objects/packages/ipackagesfactory.hpp"
#include "impl/libpkgmanifest/objects/repositories/irepositoriesfactory.hpp"
#include "impl/libpkgmanifest/objects/version/iversionfactory.hpp"
#include "impl/libpkgmanifest/operations/ipackagerepositorybinder.hpp"

namespace libpkgmanifest::internal {

constexpr const char * MANIFEST_DOCUMENT_ID = "rpm-package-manifest";

constexpr int MANIFEST_DOCUMENT_VERSION_MAJOR = 0;
constexpr int MANIFEST_DOCUMENT_VERSION_MINOR = 2;
constexpr int MANIFEST_DOCUMENT_VERSION_PATCH = 0;

class ManifestFactory : public IManifestFactory {
public:
    ManifestFactory(
        std::shared_ptr<IPackagesFactory> packages_factory,
        std::shared_ptr<IRepositoriesFactory> repositories_factory,
        std::shared_ptr<IVersionFactory> version_factory,
        std::shared_ptr<IPackageRepositoryBinder> binder);

    virtual std::unique_ptr<IManifest> create() const override;

private:
    std::shared_ptr<IPackagesFactory> packages_factory;
    std::shared_ptr<IRepositoriesFactory> repositories_factory;
    std::shared_ptr<IVersionFactory> version_factory;
    std::shared_ptr<IPackageRepositoryBinder> binder;
};

}