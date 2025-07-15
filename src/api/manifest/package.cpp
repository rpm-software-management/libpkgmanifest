// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "package_impl.hpp"

#include "api/common/repositories_impl.hpp"

#include "libpkgmanifest/manifest/package.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;

Package::Package() : p_impl(std::make_unique<Impl>()) {}

Package::~Package() = default;

Package::Package(const Package & other) : p_impl(new Impl(*other.p_impl)) {}

Package & Package::operator=(const Package & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Package::Package(Package && other) noexcept = default;
Package & Package::operator=(Package && other) noexcept = default;

std::string Package::get_repo_id() const {
    return p_impl->get()->get_repo_id();
}

std::string Package::get_location() const {
    return p_impl->get()->get_location();
}

std::string Package::get_url() const {
    return p_impl->get()->get_url();
}

uint64_t Package::get_size() const {
    return p_impl->get()->get_size();
}

Repository & Package::get_repository() const {
    return p_impl->get_repository();
}

Checksum & Package::get_checksum() {
    return p_impl->get_checksum();
}

Nevra & Package::get_nevra() {
    return p_impl->get_nevra();
}

Nevra & Package::get_srpm() {
    return p_impl->get_srpm();
}

Module & Package::get_module() {
    return p_impl->get_module();
}

void Package::set_repo_id(const std::string & repo_id) {
    p_impl->get()->set_repo_id(repo_id);
}

void Package::set_location(const std::string & location) {
    p_impl->get()->set_location(location);
}

void Package::set_size(uint64_t size) {
    p_impl->get()->set_size(size);
}

void Package::set_checksum(Checksum & checksum) {
    p_impl->get()->set_checksum(checksum.p_impl->get_owned_object());
    p_impl->get_checksum().p_impl->init(&p_impl->get()->get_checksum());
}

void Package::set_nevra(Nevra & nevra) {
    p_impl->get()->set_nevra(nevra.p_impl->get_owned_object());
    p_impl->get_nevra().p_impl->init(&p_impl->get()->get_nevra());
}

void Package::set_srpm(Nevra & srpm) {
    p_impl->get()->set_srpm(srpm.p_impl->get_owned_object());
    p_impl->get_srpm().p_impl->init(&p_impl->get()->get_srpm());
}

void Package::set_module(Module & module) {
    p_impl->get()->set_module(module.p_impl->get_owned_object());
    p_impl->get_module().p_impl->init(&p_impl->get()->get_module());
}

void Package::attach(Repositories & repositories) {
    p_impl->get_binder().bind(*repositories.p_impl->get(), *p_impl->get());
    p_impl->init(p_impl->get());
}

}