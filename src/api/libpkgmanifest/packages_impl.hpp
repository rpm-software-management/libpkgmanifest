#pragma once

#include "libpkgmanifest/packages.hpp"
#include "libpkgmanifest/package.hpp"

#include "libpkgmanifest/objects/packages/packagesfactory.hpp"

#include "package_impl.hpp"

namespace libpkgmanifest {

class Packages::Impl {
public:
    Impl() 
        : packages(nullptr)
        , factory_packages(nullptr) {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IPackages * get() {
        ensure_object_exists();
        return packages;
    }

    std::unique_ptr<internal::IPackages> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_packages);
    }

    void from_internal(internal::IPackages * packages) {
        this->packages = packages;
    }

private:
    void copy_object(const Impl & other) {
        if (other.factory_packages) {
            factory_packages = other.factory_packages->clone();
            packages = factory_packages.get();
        } else {
            packages = other.packages;
        }
    }

    void ensure_object_exists() {
        if (!packages) {
            factory_packages = internal::PackagesFactory().create();
            packages = factory_packages.get();
        }
    }

    friend Packages;
    internal::IPackages * packages;
    std::unique_ptr<internal::IPackages> factory_packages;
};

}