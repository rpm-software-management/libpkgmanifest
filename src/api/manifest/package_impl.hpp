#pragma once

#include "checksum_impl.hpp"
#include "module_impl.hpp"
#include "nevra_impl.hpp"

#include "api/common/repository_impl.hpp"
#include "impl/manifest/objects/checksum/checksumfactory.hpp"
#include "impl/manifest/objects/module/modulefactory.hpp"
#include "impl/manifest/objects/nevra/nevrafactory.hpp"
#include "impl/manifest/objects/package/packagefactory.hpp"
#include "impl/manifest/operations/packagerepositorybinder/packagerepositorybinder.hpp"

#include "libpkgmanifest/manifest/package.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;
using namespace libpkgmanifest::internal::manifest;

class Package::Impl {
public:
    Impl()
        : package(nullptr)
        , factory_package(nullptr)
        , repository()
        , checksum()
        , nevra()
        , srpm()
        , module()
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

    IPackage * get() {
        ensure_object_exists();
        return package;
    }

    std::unique_ptr<IPackage> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_package);
    }

    Repository & get_repository() {
        ensure_object_exists();
        return repository;
    }

    Checksum & get_checksum() {
        ensure_object_exists();
        return checksum;
    }

    Nevra & get_nevra() {
        ensure_object_exists();
        return nevra;
    }

    Nevra & get_srpm() {
        ensure_object_exists();
        return srpm;
    }

    Module & get_module() {
        ensure_object_exists();
        return module;
    }

    IPackageRepositoryBinder & get_binder() {
        return binder;
    }

    void init(IPackage * package) {
        this->package = package;
        checksum.p_impl->init(&package->get_checksum());
        nevra.p_impl->init(&package->get_nevra());
        srpm.p_impl->init(&package->get_srpm());
        module.p_impl->init(&package->get_module());

        // Repository information is not available at the time of object construction.
        try {
            repository.p_impl->init(&package->get_repository());
        } catch (...) {
            // TODO: Modify IMPL to handle this in a better way.
        }
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
            auto package_factory = PackageFactory(
                std::make_shared<ChecksumFactory>(),
                std::make_shared<NevraFactory>(),
                std::make_shared<ModuleFactory>()); 
            factory_package = package_factory.create();
            init(factory_package.get());
        }
    }

    IPackage * package;
    std::unique_ptr<IPackage> factory_package;
    Repository repository;
    Checksum checksum;
    Nevra nevra;
    Nevra srpm;
    Module module;
    PackageRepositoryBinder binder;
};

}