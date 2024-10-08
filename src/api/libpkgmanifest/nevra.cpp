#include "nevra_impl.hpp"

#include "libpkgmanifest/objects/nevra.hpp"

namespace libpkgmanifest {

Nevra::Nevra() : p_impl(std::make_unique<Impl>()) {}

Nevra::~Nevra() = default;

Nevra::Nevra(const Nevra & other) : p_impl(new Impl(*other.p_impl)) {}

Nevra & Nevra::operator=(const Nevra & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Nevra::Nevra(Nevra && other) noexcept = default;
Nevra & Nevra::operator=(Nevra && other) noexcept = default;

std::string Nevra::get_name() const {
    return p_impl->get()->get_name();
}

std::string Nevra::get_epoch() const {
    return p_impl->get()->get_epoch();
}

std::string Nevra::get_version() const {
    return p_impl->get()->get_version();
}

std::string Nevra::get_release() const {
    return p_impl->get()->get_release();
}

std::string Nevra::get_arch() const {
    return p_impl->get()->get_arch();
}

void Nevra::set_name(const std::string & name) {
    p_impl->get()->set_name(name);
}

void Nevra::set_epoch(const std::string & epoch) {
    p_impl->get()->set_epoch(epoch);
}

void Nevra::set_version(const std::string & version) {
    p_impl->get()->set_version(version);
}

void Nevra::set_release(const std::string & release) {
    p_impl->get()->set_release(release);
}

void Nevra::set_arch(const std::string & arch) {
    p_impl->get()->set_arch(arch);
}

std::string Nevra::to_string() const {
    return p_impl->get()->to_string();
}

}