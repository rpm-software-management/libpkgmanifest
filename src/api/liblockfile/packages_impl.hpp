#pragma once

#include "liblockfile/packages.hpp"
#include "liblockfile/package.hpp"

#include "liblockfile/objects/packages/packagesfactory.hpp"

#include "package_impl.hpp"

namespace liblockfile {

class Packages::Impl {
public:
    Impl() 
        : packages(nullptr)
        , factory_packages(nullptr) {}
    
    Impl(const Impl & other) 
        : packages(other.packages)
        , factory_packages(other.factory_packages->clone()) {}

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            packages = other.packages;
            factory_packages = other.factory_packages->clone();
        }

        return *this;
    }

    void ensure_object_exists() {
        if (!packages) {
            factory_packages = internal::PackagesFactory().create();
            packages = factory_packages.get();
        }
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
    friend Packages;
    internal::IPackages * packages;
    std::unique_ptr<internal::IPackages> factory_packages;
};

}