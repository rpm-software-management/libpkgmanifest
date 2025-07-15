// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "packages_impl.hpp"

#include "api/common/repositories_impl.hpp"
#include "api/common/version_impl.hpp"
#include "api/shared/base_impl.hpp"
#include "impl/common/objects/repositories/repositoriesfactory.hpp"
#include "impl/common/objects/version/versionfactory.hpp"
#include "impl/manifest/objects/manifest/manifestfactory.hpp"
#include "impl/manifest/objects/packages/packagesfactory.hpp"
#include "impl/manifest/operations/packagerepositorybinder/packagerepositorybinder.hpp"

#include "libpkgmanifest/manifest/manifest.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;
using namespace libpkgmanifest::internal::common;
using namespace libpkgmanifest::internal::manifest;

class Manifest::Impl : public BaseImpl<IManifest, ManifestFactory> {
public:
    Impl() = default;

    Impl(const Impl & other) : BaseImpl() {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }
        return *this;
    }

    Packages & get_packages() {
        ensure_object_exists();
        return packages;
    }

    Repositories & get_repositories() {
        ensure_object_exists();
        return repositories;
    }

    Version & get_version() {
        ensure_object_exists();
        return version;
    }

    void init(IManifest * manifest) override {
        object = manifest;
        packages.p_impl->init(&manifest->get_packages());
        repositories.p_impl->init(&manifest->get_repositories());
        version.p_impl->init(&manifest->get_version());
    }
    
protected:
    void ensure_object_exists() override {
        if (!object) {
            auto manifest_factory = ManifestFactory(
                std::make_shared<PackagesFactory>(),
                std::make_shared<RepositoriesFactory>(),
                std::make_shared<VersionFactory>(),
                std::make_shared<PackageRepositoryBinder>());
            owned_object = manifest_factory.create();
            init(owned_object.get());
        }
    }

private:
    Packages packages;
    Repositories repositories;
    Version version;
};

}