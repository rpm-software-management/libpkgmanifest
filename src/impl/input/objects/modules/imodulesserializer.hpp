// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imodules.hpp"
#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IModulesSerializer {
public:
    virtual ~IModulesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IModules & modules) const = 0;
};

}  // namespace libpkgmanifest::internal::input
