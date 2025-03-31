#pragma once

#include "checksum_impl.hpp"
#include "module_impl.hpp"
#include "nevra_impl.hpp"

#include "api/common/repository_impl.hpp"
#include "api/shared/base_impl.hpp"
#include "impl/manifest/objects/checksum/checksumfactory.hpp"
#include "impl/manifest/objects/module/modulefactory.hpp"
#include "impl/manifest/objects/nevra/nevrafactory.hpp"
#include "impl/manifest/objects/package/packagefactory.hpp"
#include "impl/manifest/operations/packagerepositorybinder/packagerepositorybinder.hpp"

#include "libpkgmanifest/manifest/package.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;
using namespace libpkgmanifest::internal::manifest;

class Package::Impl : public BaseImpl<IPackage, PackageFactory> {
    using BaseImpl<IPackage, PackageFactory>::BaseImpl;

public:
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

    void init(IPackage * package) override {
        object = package;
        checksum.p_impl->init(&package->get_checksum());
        nevra.p_impl->init(&package->get_nevra());
        srpm.p_impl->init(&package->get_srpm());
        module.p_impl->init(&package->get_module());

        // Repository information is not available at the time of object construction.
        try {
            repository.p_impl->init(&package->get_repository());
        } catch (...) {
            // TODO(jkolarik): Modify IMPL to handle this in a better way.
        }
    }

protected:
    void ensure_object_exists() override {
        if (!object) {
            auto package_factory = PackageFactory(
                std::make_shared<ChecksumFactory>(),
                std::make_shared<NevraFactory>(),
                std::make_shared<ModuleFactory>()); 
            factory_object = package_factory.create();
            init(factory_object.get());
        }
    }

private:
    Repository repository;
    Checksum checksum;
    Nevra nevra;
    Nevra srpm;
    Module module;
    PackageRepositoryBinder binder;
};

}