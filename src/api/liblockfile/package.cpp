#include "liblockfile/package.hpp"

#include "package_impl.hpp"

namespace liblockfile {

Package::Package() : p_impl(std::make_unique<Impl>()) {}

Package::Package(Package && other) noexcept : p_impl(std::move(other.p_impl)) {}

Package::~Package() = default;

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