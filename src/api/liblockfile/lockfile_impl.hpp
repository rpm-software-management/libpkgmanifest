#pragma once

#include "liblockfile/lockfile.hpp"
#include "liblockfile/packages.hpp"
#include "liblockfile/version.hpp"

#include "liblockfile/objects/lockfile/ilockfile.hpp"

#include "packages_impl.hpp"
#include "version_impl.hpp"

namespace liblockfile {

class LockFile::Impl {
public:
    ~Impl() {
        if (file) {
            delete file;
        }
    }

    const internal::ILockFile & get() const {
        return *file;
    }

    void set(std::unique_ptr<internal::ILockFile> file) {
        version.p_impl->set(file->get_version());
        packages.p_impl->set(file->get_packages());
        this->file = file.release();
    }
private:
    friend LockFile;
    internal::ILockFile * file;
    Version version;
    Packages packages;
};

}