// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "manifest.hpp"

#include "manifestfactory.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

Manifest::Manifest() : packages(nullptr), repositories(nullptr), binder(nullptr) {}

Manifest::Manifest(const Manifest & other)
    : packages(other.packages->clone()),
      repositories(other.repositories->clone()),
      binder(other.binder) {
    if (binder) {
        binder->bind(*repositories, *packages);
    }
}

std::unique_ptr<IManifest> Manifest::clone() const {
    return std::make_unique<Manifest>(*this);
}

std::string Manifest::get_document() const {
    return MANIFEST_DOCUMENT_ID;
}

const IVersion & Manifest::get_version() const {
    return MANIFEST_DOCUMENT_VERSION;
}

const IPackages & Manifest::get_packages() const {
    return *packages;
}

IPackages & Manifest::get_packages() {
    return *packages;
}

const IRepositories & Manifest::get_repositories() const {
    return *repositories;
}

IRepositories & Manifest::get_repositories() {
    return *repositories;
}

void Manifest::set_packages(std::unique_ptr<IPackages> packages) {
    this->packages = std::move(packages);
}

void Manifest::set_repositories(std::unique_ptr<IRepositories> repositories) {
    this->repositories = std::move(repositories);
}

void Manifest::set_package_repository_binder(std::shared_ptr<IPackageRepositoryBinder> binder) {
    this->binder = std::move(binder);
}

}  // namespace libpkgmanifest::internal::manifest
