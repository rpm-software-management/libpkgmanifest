#include "manifest.hpp"
#include "manifestfactory.hpp"

namespace libpkgmanifest::internal {

ManifestFactory::ManifestFactory(
    std::shared_ptr<IPackagesFactory> packages_factory,
    std::shared_ptr<IVersionFactory> version_factory)
    : packages_factory(packages_factory)
    , version_factory(version_factory) {}

std::unique_ptr<IManifest> ManifestFactory::create() const {
    auto manifest = std::make_unique<Manifest>();
    manifest->set_document(DOCUMENT_ID);
    manifest->set_packages(packages_factory->create());

    auto version = version_factory->create();
    version->set_major(DOCUMENT_VERSION_MAJOR);
    version->set_minor(DOCUMENT_VERSION_MINOR);
    version->set_patch(DOCUMENT_VERSION_PATCH);
    manifest->set_version(std::move(version));

    return manifest;
}   

}