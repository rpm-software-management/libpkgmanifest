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
    return p_impl->get()->get_document();
}

Version & LockFile::get_version() {
    return p_impl->version;
}

Packages & LockFile::get_packages() {
    return p_impl->packages;
}

void LockFile::set_document(const std::string & document) {
    p_impl->get()->set_document(document);
}

void LockFile::set_version(Version & version) {
    p_impl->version.p_impl->from_internal(version.p_impl->get());
    p_impl->get()->set_version(version.p_impl->get_factory_object());
}

void LockFile::set_packages(Packages & packages) {
    p_impl->packages.p_impl->from_internal(packages.p_impl->get());
    p_impl->get()->set_packages(packages.p_impl->get_factory_object());
}

}