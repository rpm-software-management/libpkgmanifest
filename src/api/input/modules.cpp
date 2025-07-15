// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "modules_impl.hpp"

#include "libpkgmanifest/input/modules.hpp"

namespace libpkgmanifest::input {

Modules::Modules() : p_impl(std::make_unique<Impl>()) {}

Modules::~Modules() = default;

Modules::Modules(const Modules & other) : p_impl(new Impl(*other.p_impl)) {}

Modules & Modules::operator=(const Modules & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Modules::Modules(Modules && other) noexcept = default;
Modules & Modules::operator=(Modules && other) noexcept = default;

std::vector<std::string> & Modules::get_enables() {
    return p_impl->get()->get_enables();
}

std::vector<std::string> & Modules::get_disables() {
    return p_impl->get()->get_disables();
}

}