#pragma once

#include "libpkgmanifest/manifest.hpp"
#include "libpkgmanifest/packages.hpp"
#include "libpkgmanifest/version.hpp"

#include "libpkgmanifest/objects/manifest/manifestfactory.hpp"
#include "libpkgmanifest/objects/packages/packagesfactory.hpp"
#include "libpkgmanifest/objects/version/versionfactory.hpp"

#include "packages_impl.hpp"
#include "version_impl.hpp"

namespace libpkgmanifest {

class Manifest::Impl {
public:
    Impl() 
        : manifest(nullptr)
        , factory_manifest(nullptr)
        , parsed_manifest(nullptr)
        , packages()
        , version() {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IManifest * get() {
        ensure_object_exists();
        return manifest;
    }

    std::unique_ptr<internal::IManifest> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_manifest);
    }

    Packages & get_packages() {
        ensure_object_exists();
        return packages;
    }

    Version & get_version() {
        ensure_object_exists();
        return version;
    }

    void init(internal::IManifest * manifest) {
        this->manifest = manifest;
        packages.p_impl->init(&manifest->get_packages());
        version.p_impl->init(&manifest->get_version());
    }
    
    void set(std::unique_ptr<internal::IManifest> parsed_manifest) {
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
            auto manifest_factory = internal::ManifestFactory(
                std::shared_ptr<internal::IPackagesFactory>(new internal::PackagesFactory()), 
                std::shared_ptr<internal::IVersionFactory>(new internal::VersionFactory()));
            factory_manifest = manifest_factory.create();
            init(factory_manifest.get());
        }
    }

    internal::IManifest * manifest;
    std::unique_ptr<internal::IManifest> factory_manifest;
    std::unique_ptr<internal::IManifest> parsed_manifest;
    Packages packages;
    Version version;
};

}