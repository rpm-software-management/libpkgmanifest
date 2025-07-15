// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iinput.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

class IInputParser {
public:
    virtual ~IInputParser() = default;

    virtual std::unique_ptr<IInput> parse(const IYamlNode & node) const = 0;
};

}