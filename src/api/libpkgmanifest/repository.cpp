#include "repository_impl.hpp"

#include "libpkgmanifest/repository.hpp"

namespace libpkgmanifest {

Repository::Repository() : p_impl(std::make_unique<Impl>()) {}

Repository::~Repository() = default;

Repository::Repository(const Repository & other) : p_impl(new Impl(*other.p_impl)) {}

Repository & Repository::operator=(const Repository & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Repository::Repository(Repository && other) noexcept = default;
Repository & Repository::operator=(Repository && other) noexcept = default;

std::string Repository::get_id() const {
    return p_impl->get()->get_id();
}

std::string Repository::get_url() const {
    return p_impl->get()->get_url();
}

void Repository::set_id(const std::string & id) {
    p_impl->get()->set_id(id);
}

void Repository::set_url(const std::string & url) {
    p_impl->get()->set_url(url);
}

}