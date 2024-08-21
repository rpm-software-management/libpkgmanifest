#pragma once

#include "libpkgmanifest/package.hpp"
#include "libpkgmanifest/checksum.hpp"

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

    void from_internal(internal::IPackage * package) {
        this->package = package;
        checksum.p_impl->from_internal(&package->get_checksum());
    }

private:
    void copy_object(const Impl & other) {
        checksum = std::move(other.checksum);

        if (other.factory_package) {
            factory_package = other.factory_package->clone();
            from_internal(factory_package.get());
        } else {
            from_internal(other.package);
        }
    }

    void ensure_object_exists() {
        if (!package) {
            factory_package = internal::PackageFactory().create();
            package = factory_package.get();
            package->set_checksum(checksum.p_impl->get_factory_object());
        }
    }

    friend Package;
    internal::IPackage * package;
    std::unique_ptr<internal::IPackage> factory_package;
    Checksum checksum;
};

}