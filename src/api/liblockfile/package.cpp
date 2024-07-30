#include "package_impl.hpp"

#include "liblockfile/package.hpp"

namespace liblockfile {

Package::Package() : p_impl(std::make_unique<Impl>()) {}

Package::~Package() = default;

Package::Package(const Package & other) : p_impl(new Impl(*other.p_impl)) {}

Package & Package::operator=(const Package & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Package::Package(Package && other) noexcept = default;
Package & Package::operator=(Package && other) noexcept = default;

std::string Package::get_arch() const {
    return p_impl->package->get_arch();
}

std::string Package::get_repo_id() const {
    return p_impl->package->get_repo_id();
}

std::string Package::get_url() const {
    return p_impl->package->get_url();
}

const Checksum & Package::get_checksum() const {
    return p_impl->checksum;
}

uint64_t Package::get_size() const {
    return p_impl->package->get_size();
}

std::string Package::get_nevra() const {
    return p_impl->package->get_nevra();
}

std::string Package::get_srpm() const {
    return p_impl->package->get_srpm();
}

}