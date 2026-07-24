// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "ipackages.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IPackagesParser {
public:
    virtual ~IPackagesParser() = default;

    virtual std::unique_ptr<IPackages> parse(const IYamlNode & node) const = 0;
};

}  // namespace libpkgmanifest::internal::manifest
