#pragma once

#include "liblockfile/lockfile.hpp"
#include "liblockfile/packages.hpp"
#include "liblockfile/version.hpp"

#include "liblockfile/objects/lockfile/lockfilefactory.hpp"

#include "packages_impl.hpp"
#include "version_impl.hpp"

namespace liblockfile {

class LockFile::Impl {
public:
    Impl() 
        : file(nullptr)
        , factory_file(nullptr)
        , parsed_file(nullptr)
        , version()
        , packages() {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::ILockFile * get() {
        ensure_object_exists();
        return file;
    }

    std::unique_ptr<internal::ILockFile> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_file);
    }

    void from_internal(internal::ILockFile * file) {
        this->file = file;
        version.p_impl->from_internal(&file->get_version());
        packages.p_impl->from_internal(&file->get_packages());
    }
    
    void set(std::unique_ptr<internal::ILockFile> parsed_file) {
        from_internal(parsed_file.get());
        this->parsed_file = std::move(parsed_file);
    }

private:
    void copy_object(const Impl & other) {
        version = other.version;
        packages = other.packages;

        if (other.parsed_file) {
            parsed_file = other.parsed_file->clone();
            from_internal(parsed_file.get());
        } else if (other.factory_file) {
            factory_file = other.factory_file->clone();
            from_internal(factory_file.get());
        }
    }

    void ensure_object_exists() {
        if (!file) {
            factory_file = internal::LockFileFactory().create();
            file = factory_file.get();
            file->set_version(version.p_impl->get_factory_object());
            file->set_packages(packages.p_impl->get_factory_object());
        }
    }

    friend LockFile;
    internal::ILockFile * file;
    std::unique_ptr<internal::ILockFile> factory_file;
    std::unique_ptr<internal::ILockFile> parsed_file;
    Version version;
    Packages packages;
};

}