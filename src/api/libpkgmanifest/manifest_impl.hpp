#pragma once

#include "libpkgmanifest/manifest.hpp"
#include "libpkgmanifest/packages.hpp"
#include "libpkgmanifest/version.hpp"

#include "libpkgmanifest/objects/manifest/manifestfactory.hpp"

#include "packages_impl.hpp"
#include "version_impl.hpp"

namespace libpkgmanifest {

class Manifest::Impl {
public:
    Impl() 
        : manifest(nullptr)
        , factory_manifest(nullptr)
        , parsed_manifest(nullptr)
        , version()
        , packages() {}

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

    void from_internal(internal::IManifest * manifest) {
        this->manifest = manifest;
        version.p_impl->from_internal(&manifest->get_version());
        packages.p_impl->from_internal(&manifest->get_packages());
    }
    
    void set(std::unique_ptr<internal::IManifest> parsed_manifest) {
        from_internal(parsed_manifest.get());
        this->parsed_manifest = std::move(parsed_manifest);
    }

private:
    void copy_object(const Impl & other) {
        version = other.version;
        packages = other.packages;

        if (other.parsed_manifest) {
            parsed_manifest = other.parsed_manifest->clone();
            from_internal(parsed_manifest.get());
        } else if (other.factory_manifest) {
            factory_manifest = other.factory_manifest->clone();
            from_internal(factory_manifest.get());
        }
    }

    void ensure_object_exists() {
        if (!manifest) {
            factory_manifest = internal::ManifestFactory().create();
            manifest = factory_manifest.get();
            manifest->set_version(version.p_impl->get_factory_object());
            manifest->set_packages(packages.p_impl->get_factory_object());
        }
    }

    friend Manifest;
    internal::IManifest * manifest;
    std::unique_ptr<internal::IManifest> factory_manifest;
    std::unique_ptr<internal::IManifest> parsed_manifest;
    Version version;
    Packages packages;
};

}