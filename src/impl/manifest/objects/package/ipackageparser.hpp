// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackage.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IPackageParser {
public:
    virtual ~IPackageParser() = default;

    virtual std::unique_ptr<IPackage> parse(const std::string & arch, const IYamlNode & node) const = 0;
};

}