#pragma once

#include "liblockfile/checksum.hpp"

#include "liblockfile/objects/checksum/checksumfactory.hpp"

namespace liblockfile {

class Checksum::Impl {
public:
    Impl() 
        : checksum(nullptr)
        , factory_checksum(nullptr) {}
    
    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IChecksum * get() {
        ensure_object_exists();
        return checksum;
    }

    std::unique_ptr<internal::IChecksum> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_checksum);
    }

    void from_internal(internal::IChecksum * checksum) {
        this->checksum = checksum;
    }

private:
    void copy_object(const Impl & other) {
        if (other.factory_checksum) {
            factory_checksum = other.factory_checksum->clone();
            checksum = factory_checksum.get();
        } else {
            checksum = other.checksum;
        }
    }

    void ensure_object_exists() {
        if (!checksum) {
            factory_checksum = internal::ChecksumFactory().create();
            checksum = factory_checksum.get();
        }
    }

    friend Checksum;
    internal::IChecksum * checksum;
    std::unique_ptr<internal::IChecksum> factory_checksum;
};

}