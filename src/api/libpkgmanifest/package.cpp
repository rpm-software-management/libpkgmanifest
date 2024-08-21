#include "package_impl.hpp"

#include "libpkgmanifest/package.hpp"

namespace libpkgmanifest {

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
    return p_impl->get()->get_arch();
}

std::string Package::get_repo_id() const {
    return p_impl->get()->get_repo_id();
}

std::string Package::get_url() const {
    return p_impl->get()->get_url();
}

Checksum & Package::get_checksum() {
    return p_impl->checksum;
}

uint64_t Package::get_size() const {
    return p_impl->get()->get_size();
}

std::string Package::get_nevra() const {
    return p_impl->get()->get_nevra();
}

std::string Package::get_srpm() const {
    return p_impl->get()->get_srpm();
}

void Package::set_arch(const std::string & arch) {
    p_impl->get()->set_arch(arch);
}

void Package::set_repo_id(const std::string & repo_id) {
    p_impl->get()->set_repo_id(repo_id);
}

void Package::set_url(const std::string & url) {
    p_impl->get()->set_url(url);
}

void Package::set_checksum(Checksum & checksum) {
    p_impl->checksum.p_impl->from_internal(checksum.p_impl->get());
    p_impl->get()->set_checksum(checksum.p_impl->get_factory_object());
}

void Package::set_size(uint64_t size) {
    p_impl->get()->set_size(size);
}

void Package::set_nevra(const std::string & nevra) {
    p_impl->get()->set_nevra(nevra);
}

void Package::set_srpm(const std::string & srpm) {
    p_impl->get()->set_srpm(srpm);
}

}