// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "irepositories.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoriesSerializer {
public:
    virtual ~IRepositoriesSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IRepositories & packages) const = 0;
};

}