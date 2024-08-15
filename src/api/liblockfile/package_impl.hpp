#pragma once

#include "liblockfile/package.hpp"
#include "liblockfile/checksum.hpp"

#include "liblockfile/objects/package/packagefactory.hpp"

#include "checksum_impl.hpp"

namespace liblockfile {

class Package::Impl {
public:
    Impl()
        : package(nullptr)
        , factory_package(nullptr)
        , checksum() {}
    
    Impl(const Impl & other) 
        : package(other.package)
        , factory_package(other.factory_package->clone())
        , checksum(other.checksum) {}

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            package = other.package;
            factory_package = other.factory_package->clone();
            checksum = other.checksum;
        }

        return *this;
    }

    void ensure_object_exists() {
        if (!package) {
            factory_package = internal::PackageFactory().create();
            package = factory_package.get();
            package->set_checksum(checksum.p_impl->get_factory_object());
        }
    }
    
    internal::IPackage * get() {
        ensure_object_exists();
        return package;
    }

    std::unique_ptr<internal::IPackage> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_package);
    }
    
    void from_internal(internal::IPackage * package) {
        this->package = package;
        checksum.p_impl->from_internal(&package->get_checksum());
    }

private:
    friend Package;
    internal::IPackage * package;
    std::unique_ptr<internal::IPackage> factory_package;
    Checksum checksum;
};

}