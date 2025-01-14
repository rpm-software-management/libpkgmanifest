#pragma once

#include "packages_impl.hpp"

#include "api/common/repositories_impl.hpp"
#include "api/common/version_impl.hpp"
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

class Manifest::Impl {
public:
    Impl() = default;

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    IManifest * get() {
        ensure_object_exists();
        return manifest;
    }

    std::unique_ptr<IManifest> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_manifest);
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

    void init(IManifest * manifest) {
        this->manifest = manifest;
        packages.p_impl->init(&manifest->get_packages());
        repositories.p_impl->init(&manifest->get_repositories());
        version.p_impl->init(&manifest->get_version());
    }
    
    void set(std::unique_ptr<IManifest> parsed_manifest) {
        init(parsed_manifest.get());
        this->parsed_manifest = std::move(parsed_manifest);
    }

private:
    void copy_object(const Impl & other) {
        if (other.parsed_manifest) {
            parsed_manifest = other.parsed_manifest->clone();
            init(parsed_manifest.get());
        } else if (other.factory_manifest) {
            factory_manifest = other.factory_manifest->clone();
            init(factory_manifest.get());
        }
    }

    void ensure_object_exists() {
        if (!manifest) {
            auto manifest_factory = ManifestFactory(
                std::make_shared<PackagesFactory>(),
                std::make_shared<RepositoriesFactory>(),
                std::make_shared<VersionFactory>(),
                std::make_shared<PackageRepositoryBinder>());
            factory_manifest = manifest_factory.create();
            init(factory_manifest.get());
        }
    }

    IManifest * manifest = nullptr;
    std::unique_ptr<IManifest> factory_manifest;
    std::unique_ptr<IManifest> parsed_manifest;
    Packages packages;
    Repositories repositories;
    Version version;
};

}