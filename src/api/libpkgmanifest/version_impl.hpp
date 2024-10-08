#pragma once

#include "libpkgmanifest/objects/version.hpp"

#include "impl/libpkgmanifest/objects/version/versionfactory.hpp"

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

    void init(internal::IVersion * version) {
        this->version = version;
    }

private:
    void copy_object(const Impl & other) {
        if (other.version) {
            init(other.version);
        } else if (other.factory_version) {
            factory_version = other.factory_version->clone();
            init(factory_version.get());
        }
    }

    void ensure_object_exists() {
        if (!version) {
            factory_version = internal::VersionFactory().create();
            init(factory_version.get());
        }
    }

    internal::IVersion * version;
    std::unique_ptr<internal::IVersion> factory_version;
};

}