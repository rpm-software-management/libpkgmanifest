// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "irepositories.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoriesSerializer {
public:
    virtual ~IRepositoriesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IRepositories & packages) const = 0;
};

}  // namespace libpkgmanifest::internal::common
