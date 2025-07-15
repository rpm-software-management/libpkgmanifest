// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "checksum_impl.hpp"

#include "libpkgmanifest/manifest/checksum.hpp"

namespace libpkgmanifest::manifest {

Checksum::Checksum() : p_impl(std::make_unique<Impl>()) {}

Checksum::~Checksum() = default;

Checksum::Checksum(const Checksum & other) : p_impl(new Impl(*other.p_impl)) {}

Checksum & Checksum::operator=(const Checksum & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Checksum::Checksum(Checksum && other) noexcept = default;
Checksum & Checksum::operator=(Checksum && other) noexcept = default;

ChecksumMethod Checksum::get_method() const {
    return p_impl->get()->get_method();
}
    
std::string Checksum::get_digest() const {
    return p_impl->get()->get_digest();
}

void Checksum::set_method(ChecksumMethod method) {
    p_impl->get()->set_method(method);
}

void Checksum::set_digest(const std::string & digest) {
    p_impl->get()->set_digest(digest);
}

}