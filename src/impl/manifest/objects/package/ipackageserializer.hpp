// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "ipackage.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IPackageSerializer {
public:
    virtual ~IPackageSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IPackage & package) const = 0;
};

}  // namespace libpkgmanifest::internal::manifest
