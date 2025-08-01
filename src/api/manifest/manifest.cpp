// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "manifest_impl.hpp"

#include "libpkgmanifest/manifest/manifest.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;

Manifest::Manifest() : p_impl(std::make_unique<Impl>()) {}

Manifest::~Manifest() = default;

Manifest::Manifest(const Manifest & other) : p_impl(new Impl(*other.p_impl)) {}

Manifest & Manifest::operator=(const Manifest & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Manifest::Manifest(Manifest && other) noexcept = default;
Manifest & Manifest::operator=(Manifest && other) noexcept = default;

std::string Manifest::get_document() const {
    return p_impl->get()->get_document();
}

Version & Manifest::get_version() {
    return p_impl->get_version();
}

Packages & Manifest::get_packages() {
    return p_impl->get_packages();
}

Repositories & Manifest::get_repositories() {
    return p_impl->get_repositories();
}

void Manifest::set_document(const std::string & document) {
    p_impl->get()->set_document(document);
}

void Manifest::set_version(Version & version) {
    p_impl->get()->set_version(version.p_impl->get_owned_object());
    p_impl->get_version().p_impl->init(&p_impl->get()->get_version());
}

void Manifest::set_packages(Packages & packages) {
    p_impl->get()->set_packages(packages.p_impl->get_owned_object());
    p_impl->get_packages().p_impl->init(&p_impl->get()->get_packages());
}

void Manifest::set_repositories(Repositories & repositories) {
    p_impl->get()->set_repositories(repositories.p_impl->get_owned_object());
    p_impl->get_repositories().p_impl->init(&p_impl->get()->get_repositories());
}

}