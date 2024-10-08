#pragma once

#include "libpkgmanifest/objects/packages.hpp"

#include "impl/libpkgmanifest/objects/packages/packagesfactory.hpp"
#include "impl/libpkgmanifest/operations/packagerepositorybinder.hpp"

#include "package_impl.hpp"

namespace libpkgmanifest {

class Packages::Impl {
public:
    Impl() 
        : packages(nullptr)
        , factory_packages(nullptr)
        , binder() {}

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

    internal::IPackageRepositoryBinder & get_binder() {
        return binder;
    }

    void init(internal::IPackages * packages) {
        this->packages = packages;
    }

    Package wrap_internal_item(internal::IPackage * package) const {
        Package wrapped_package;
        wrapped_package.p_impl->init(package);
        return wrapped_package;
    }

    std::vector<Package> wrap_internal_items(const std::vector<std::unique_ptr<internal::IPackage>> & packages) const {
        std::vector<Package> wrapped_packages;
        wrapped_packages.reserve(packages.size());
        for (const auto & package : packages) {
            wrapped_packages.push_back(wrap_internal_item(package.get()));
        }
        return wrapped_packages;
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
            factory_packages = internal::PackagesFactory().create();
            init(factory_packages.get());
        }
    }

    internal::IPackages * packages;
    std::unique_ptr<internal::IPackages> factory_packages;
    internal::PackageRepositoryBinder binder;
};

}