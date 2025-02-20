#pragma once

#include "imanifestfactory.hpp"

#include "impl/common/objects/repositories/irepositoriesfactory.hpp"
#include "impl/common/objects/version/iversionfactory.hpp"
#include "impl/manifest/objects/packages/ipackagesfactory.hpp"
#include "impl/manifest/operations/packagerepositorybinder/ipackagerepositorybinder.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

constexpr const char * MANIFEST_DOCUMENT_ID = "rpm-package-manifest";

constexpr int MANIFEST_DOCUMENT_VERSION_MAJOR = 0;
constexpr int MANIFEST_DOCUMENT_VERSION_MINOR = 2;
constexpr int MANIFEST_DOCUMENT_VERSION_PATCH = 2;

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