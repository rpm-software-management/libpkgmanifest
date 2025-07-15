// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "module.hpp"

namespace libpkgmanifest::internal::manifest {

Module::Module()
    : name()
    , stream() {}

std::unique_ptr<IModule> Module::clone() const {
    return std::make_unique<Module>(*this);
}

std::string Module::get_name() const {
    return name;
}

std::string Module::get_stream() const {
    return stream;
}

void Module::set_name(const std::string & name) {
    this->name = name;
}

void Module::set_stream(const std::string & stream) {
    this->stream = stream;
}

}