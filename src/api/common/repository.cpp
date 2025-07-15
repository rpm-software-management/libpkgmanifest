// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "repository_impl.hpp"

#include "libpkgmanifest/common/repository.hpp"

namespace libpkgmanifest::common {

Repository::Repository() : p_impl(std::make_unique<Impl>()) {}

Repository::~Repository() = default;

Repository::Repository(const Repository & other) : p_impl(new Impl(*other.p_impl)) {}

Repository & Repository::operator=(const Repository & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Repository::Repository(Repository && other) noexcept = default;
Repository & Repository::operator=(Repository && other) noexcept = default;

std::string Repository::get_id() const {
    return p_impl->get()->get_id();
}

std::string Repository::get_baseurl() const {
    return p_impl->get()->get_baseurl();
}

std::string Repository::get_metalink() const {
    return p_impl->get()->get_metalink();
}

std::string Repository::get_mirrorlist() const {
    return p_impl->get()->get_mirrorlist();
}

void Repository::set_id(const std::string & id) {
    p_impl->get()->set_id(id);
}

void Repository::set_baseurl(const std::string & baseurl) {
    p_impl->get()->set_baseurl(baseurl);
}

void Repository::set_metalink(const std::string & metalink) {
    p_impl->get()->set_metalink(metalink);
}

void Repository::set_mirrorlist(const std::string & mirrorlist) {
    p_impl->get()->set_mirrorlist(mirrorlist);
}

}