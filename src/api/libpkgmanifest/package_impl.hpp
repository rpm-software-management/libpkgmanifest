#pragma once

#include "libpkgmanifest/package.hpp"
#include "libpkgmanifest/checksum.hpp"
#include "libpkgmanifest/module.hpp"
#include "libpkgmanifest/nevra.hpp"

#include "libpkgmanifest/objects/checksum/checksumfactory.hpp"
#include "libpkgmanifest/objects/module/modulefactory.hpp"
#include "libpkgmanifest/objects/nevra/nevrafactory.hpp"
#include "libpkgmanifest/objects/package/packagefactory.hpp"

#include "checksum_impl.hpp"
#include "module_impl.hpp"
#include "nevra_impl.hpp"

namespace libpkgmanifest {

class Package::Impl {
public:
    Impl()
        : package(nullptr)
        , factory_package(nullptr)
        , checksum()
        , nevra()
        , srpm()
        , module() {}

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

    void init(internal::IPackage * package) {
        this->package = package;
        checksum.p_impl->init(&package->get_checksum());
        nevra.p_impl->init(&package->get_nevra());
        srpm.p_impl->init(&package->get_srpm());
        module.p_impl->init(&package->get_module());
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
                std::shared_ptr<internal::IChecksumFactory>(new internal::ChecksumFactory()),
                std::shared_ptr<internal::INevraFactory>(new internal::NevraFactory()),
                std::shared_ptr<internal::IModuleFactory>(new internal::ModuleFactory())); 
            factory_package = package_factory.create();
            init(factory_package.get());
        }
    }

    internal::IPackage * package;
    std::unique_ptr<internal::IPackage> factory_package;
    Checksum checksum;
    Nevra nevra;
    Nevra srpm;
    Module module;
};

}