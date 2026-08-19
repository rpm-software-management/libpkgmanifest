// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "ipackages.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IPackagesSerializer {
public:
    virtual ~IPackagesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackages & packages) const = 0;
};

}  // namespace libpkgmanifest::internal::input
