#pragma once

#include "libpkgmanifest/version.hpp"

#include "libpkgmanifest/objects/version/versionfactory.hpp"

namespace libpkgmanifest {

class Version::Impl {
public:
    Impl() 
        : version(nullptr)
        , factory_version(nullptr) {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IVersion * get() {
        ensure_object_exists();
        return version;
    }

    std::unique_ptr<internal::IVersion> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_version);
    }

    void from_internal(internal::IVersion * version) {
        this->version = version;
    }

private:
    void copy_object(const Impl & other) {
        if (other.factory_version) {
            factory_version = other.factory_version->clone();
            version = factory_version.get();
        } else {
            version = other.version;
        }
    }

    void ensure_object_exists() {
        if (!version) {
            factory_version = internal::VersionFactory().create();
            version = factory_version.get();
        }
    }

    friend Version;
    internal::IVersion * version;
    std::unique_ptr<internal::IVersion> factory_version;
};

}