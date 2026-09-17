// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "manifestfactory.hpp"

#include "manifest.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

ManifestFactory::ManifestFactory(
    std::shared_ptr<IPackagesFactory> packages_factory,
    std::shared_ptr<IRepositoriesFactory> repositories_factory,
    std::shared_ptr<IPackageRepositoryBinder> binder)
    : packages_factory(std::move(packages_factory)),
      repositories_factory(std::move(repositories_factory)),
      binder(std::move(binder)) {}

std::unique_ptr<IManifest> ManifestFactory::create() const {
    auto manifest = std::make_unique<Manifest>();
    manifest->set_repositories(repositories_factory->create());
    manifest->set_packages(packages_factory->create());
    manifest->set_package_repository_binder(binder);

    return manifest;
}

}  // namespace libpkgmanifest::internal::manifest
