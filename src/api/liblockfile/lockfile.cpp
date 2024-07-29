#include "liblockfile/lockfile.hpp"

#include "lockfile_impl.hpp"

namespace liblockfile {

LockFile::LockFile() : p_impl(std::make_unique<Impl>()) {}

LockFile::LockFile(LockFile && other) noexcept : p_impl(std::move(other.p_impl)) {}

LockFile::~LockFile() = default;

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