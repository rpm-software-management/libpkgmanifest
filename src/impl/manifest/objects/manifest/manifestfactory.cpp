#include "manifest.hpp"
#include "manifestfactory.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

ManifestFactory::ManifestFactory(
    std::shared_ptr<IPackagesFactory> packages_factory,
    std::shared_ptr<IRepositoriesFactory> repositories_factory,
    std::shared_ptr<IVersionFactory> version_factory,
    std::shared_ptr<IPackageRepositoryBinder> binder)
    : packages_factory(std::move(packages_factory))
    , repositories_factory(std::move(repositories_factory))
    , version_factory(std::move(version_factory))
    , binder(std::move(binder)) {}

std::unique_ptr<IManifest> ManifestFactory::create() const {
    auto manifest = std::make_unique<Manifest>();
    manifest->set_document(MANIFEST_DOCUMENT_ID);
    manifest->set_repositories(repositories_factory->create());
    manifest->set_packages(packages_factory->create());
    manifest->set_package_repository_binder(binder);

    auto version = version_factory->create();
    version->set_major(MANIFEST_DOCUMENT_VERSION_MAJOR);
    version->set_minor(MANIFEST_DOCUMENT_VERSION_MINOR);
    version->set_patch(MANIFEST_DOCUMENT_VERSION_PATCH);
    manifest->set_version(std::move(version));

    return manifest;
}   

}