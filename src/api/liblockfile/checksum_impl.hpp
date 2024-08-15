#pragma once

#include "liblockfile/checksum.hpp"

#include "liblockfile/objects/checksum/checksumfactory.hpp"

namespace liblockfile {

class Checksum::Impl {
public:
    Impl() 
        : checksum(nullptr)
        , factory_checksum(nullptr) {}
    
    Impl(const Impl & other) 
        : checksum(other.checksum)
        , factory_checksum(other.checksum->clone()) {}

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            checksum = other.checksum;
            factory_checksum = other.factory_checksum->clone();
        }

        return *this;
    }

    void ensure_object_exists() {
        if (!checksum) {
            factory_checksum = internal::ChecksumFactory().create();
            checksum = factory_checksum.get();
        }
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
    friend Checksum;
    internal::IChecksum * checksum;
    std::unique_ptr<internal::IChecksum> factory_checksum;
};

}