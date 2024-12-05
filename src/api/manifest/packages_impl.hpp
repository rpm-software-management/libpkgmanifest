#pragma once

#include "libpkgmanifest/manifest/packages.hpp"

#include "impl/manifest/objects/packages/packagesfactory.hpp"
#include "impl/manifest/operations/packagerepositorybinder/packagerepositorybinder.hpp"

#include "package_impl.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

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

    IPackages * get() {
        ensure_object_exists();
        return packages;
    }

    std::unique_ptr<IPackages> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_packages);
    }

    IPackageRepositoryBinder & get_binder() {
        return binder;
    }

    void init(IPackages * packages) {
        this->packages = packages;
    }

    Package wrap_internal_item(IPackage * package) const {
        Package wrapped_package;
        wrapped_package.p_impl->init(package);
        return wrapped_package;
    }

    std::vector<Package> wrap_internal_items(const std::vector<std::unique_ptr<IPackage>> & packages) const {
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
            factory_packages = PackagesFactory().create();
            init(factory_packages.get());
        }
    }

    IPackages * packages;
    std::unique_ptr<IPackages> factory_packages;
    PackageRepositoryBinder binder;
};

}