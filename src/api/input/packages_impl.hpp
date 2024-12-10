#pragma once

#include "libpkgmanifest/input/packages.hpp"

#include "impl/input/objects/packages/packagesfactory.hpp"

namespace libpkgmanifest::input {

using namespace libpkgmanifest::internal::input;

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

    IPackages * get() {
        ensure_object_exists();
        return packages;
    }

    std::unique_ptr<IPackages> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_packages);
    }

    void init(IPackages * packages) {
        this->packages = packages;
    }

private:
    void copy_object(const Impl & other) {
        if (other.packages) {
            init(other.packages);
        } else if (other.factory_packages) {
            factory_packages = other.factory_packages->clone();
            init(factory_packages.get());
        }
    }

    void ensure_object_exists() {
        if (!packages) {
            factory_packages = PackagesFactory().create();
            init(factory_packages.get());
        }
    }

    IPackages * packages;
    std::unique_ptr<IPackages> factory_packages;
};

}