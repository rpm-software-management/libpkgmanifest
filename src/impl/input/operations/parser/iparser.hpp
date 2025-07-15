// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/input/objects/input/iinput.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal::input {

class IParser {
public:
    virtual ~IParser() = default;

    virtual std::unique_ptr<IInput> parse(const std::string & path) const = 0;
    virtual std::unique_ptr<IInput> parse_from_prototype(const std::string & path) const = 0;
};

}