#include "lockfile_impl.hpp"

#include "liblockfile/lockfile.hpp"

namespace liblockfile {

LockFile::LockFile() : p_impl(std::make_unique<Impl>()) {}

LockFile::~LockFile() = default;

LockFile::LockFile(const LockFile & other) : p_impl(new Impl(*other.p_impl)) {}

LockFile & LockFile::operator=(const LockFile & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

LockFile::LockFile(LockFile && other) noexcept = default;
LockFile & LockFile::operator=(LockFile && other) noexcept = default;

std::string LockFile::get_document() const {
    return p_impl->file->get_document();
}

const Version & LockFile::get_version() const {
    return p_impl->version;
}

const Packages & LockFile::get_packages() const {
    return p_impl->packages;
}

}