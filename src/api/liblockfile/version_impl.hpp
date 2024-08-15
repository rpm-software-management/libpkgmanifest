#pragma once

#include "liblockfile/version.hpp"

#include "liblockfile/objects/version/versionfactory.hpp"

namespace liblockfile {

class Version::Impl {
public:
    Impl() 
        : version(nullptr)
        , factory_version(nullptr) {}
    
    Impl(const Impl & other) 
        : version(other.version)
        , factory_version(other.version->clone()) {}

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            version = other.version;
            factory_version = other.factory_version->clone();
        }

        return *this;
    }

    void ensure_object_exists() {
        if (!version) {
            factory_version = internal::VersionFactory().create();
            version = factory_version.get();
        }
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
    friend Version;
    internal::IVersion * version;
    std::unique_ptr<internal::IVersion> factory_version;
};

}