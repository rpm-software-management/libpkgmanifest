#pragma once

#include "libpkgmanifest/package.hpp"
#include "libpkgmanifest/checksum.hpp"

#include "libpkgmanifest/objects/checksum/checksumfactory.hpp"
#include "libpkgmanifest/objects/package/packagefactory.hpp"

#include "checksum_impl.hpp"

namespace libpkgmanifest {

class Package::Impl {
public:
    Impl()
        : package(nullptr)
        , factory_package(nullptr)
        , checksum() {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IPackage * get() {
        ensure_object_exists();
        return package;
    }

    std::unique_ptr<internal::IPackage> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_package);
    }

    Checksum & get_checksum() {
        ensure_object_exists();
        return checksum;
    }

    void init(internal::IPackage * package) {
        this->package = package;
        checksum.p_impl->init(&package->get_checksum());
    }

private:
    void copy_object(const Impl & other) {
        if (other.package) {
            init(other.package);
        } else if (other.factory_package) {
            factory_package = other.factory_package->clone();
            init(factory_package.get());
        }
    }

    void ensure_object_exists() {
        if (!package) {
            auto package_factory = internal::PackageFactory(
                std::shared_ptr<internal::IChecksumFactory>(new internal::ChecksumFactory())); 
            factory_package = package_factory.create();
            init(factory_package.get());
        }
    }

    internal::IPackage * package;
    std::unique_ptr<internal::IPackage> factory_package;
    Checksum checksum;
};

}