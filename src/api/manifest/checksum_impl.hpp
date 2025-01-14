#pragma once

#include "libpkgmanifest/manifest/checksum.hpp"

#include "impl/manifest/objects/checksum/checksumfactory.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Checksum::Impl {
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

    IChecksum * get() {
        ensure_object_exists();
        return checksum;
    }

    std::unique_ptr<IChecksum> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_checksum);
    }

    void init(IChecksum * checksum) {
        this->checksum = checksum;
    }

private:
    void copy_object(const Impl & other) {
        if (other.checksum) {
            init(other.checksum);
        } else if (other.factory_checksum) {
            factory_checksum = other.factory_checksum->clone();
            init(factory_checksum.get());
        }
    }

    void ensure_object_exists() {
        if (!checksum) {
            factory_checksum = ChecksumFactory().create();
            init(factory_checksum.get());
        }
    }

    IChecksum * checksum = nullptr;
    std::unique_ptr<IChecksum> factory_checksum;
};

}