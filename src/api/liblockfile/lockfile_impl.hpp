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
    
    Impl(const Impl & other) 
        : file(other.file)
        , factory_file(other.factory_file->clone())
        , parsed_file(other.parsed_file->clone())
        , version(other.version)
        , packages(other.packages) {}

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            file = other.file;
            factory_file = other.factory_file->clone();
            parsed_file = other.parsed_file->clone();
            version = other.version;
            packages = other.packages;
        }

        return *this;
    }

    void ensure_object_exists() {
        if (!file) {
            factory_file = internal::LockFileFactory().create();
            file = factory_file.get();
            file->set_version(version.p_impl->get_factory_object());
            file->set_packages(packages.p_impl->get_factory_object());
        }
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
    friend LockFile;
    internal::ILockFile * file;
    std::unique_ptr<internal::ILockFile> factory_file;
    std::unique_ptr<internal::ILockFile> parsed_file;
    Version version;
    Packages packages;
};

}