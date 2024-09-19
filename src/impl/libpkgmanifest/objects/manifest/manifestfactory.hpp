#pragma once

#include "imanifestfactory.hpp"

#include "libpkgmanifest/objects/packages/ipackagesfactory.hpp"
#include "libpkgmanifest/objects/version/iversionfactory.hpp"

namespace libpkgmanifest::internal {

constexpr const char * DOCUMENT_ID = "rpm-package-manifest";

constexpr int DOCUMENT_VERSION_MAJOR = 0;
constexpr int DOCUMENT_VERSION_MINOR = 0;
constexpr int DOCUMENT_VERSION_PATCH = 2;

class ManifestFactory : public IManifestFactory {
public:
    ManifestFactory(
        std::shared_ptr<IPackagesFactory> packages_factory,
        std::shared_ptr<IVersionFactory> version_factory);

    virtual std::unique_ptr<IManifest> create() const override;

private:
    std::shared_ptr<IPackagesFactory> packages_factory;
    std::shared_ptr<IVersionFactory> version_factory;
};

}