// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iinput.hpp"
#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IInputSerializer {
public:
    virtual ~IInputSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IInput & input) const = 0;
};

}  // namespace libpkgmanifest::internal::input
