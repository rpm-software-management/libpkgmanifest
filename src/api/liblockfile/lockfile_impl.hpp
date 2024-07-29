#pragma once

#include "liblockfile/lockfile.hpp"
#include "liblockfile/packages.hpp"
#include "liblockfile/version.hpp"

#include "liblockfile/objects/lockfile/ilockfile.hpp"

#include "packages_impl.hpp"
#include "version_impl.hpp"

#include <memory>

namespace liblockfile {

class LockFile::Impl {
public:
    const internal::ILockFile & get() const {
        return *file;
    }

    void set(std::unique_ptr<internal::ILockFile> file) {
        version.p_impl->set(file->get_version());
        packages.p_impl->set(file->get_packages());
        this->file = std::move(file);
    }
private:
    friend LockFile;
    std::unique_ptr<internal::ILockFile> file;
    Version version;
    Packages packages;
};

}