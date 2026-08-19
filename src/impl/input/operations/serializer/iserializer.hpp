// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/input/objects/input/iinput.hpp"

#include <string>

namespace libpkgmanifest::internal::input {

class ISerializer {
public:
    virtual ~ISerializer() = default;

    virtual void serialize_input(const IInput & input, const std::string & path) const = 0;
};

}  // namespace libpkgmanifest::internal::input
