// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "irepository.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositorySerializer {
public:
    virtual ~IRepositorySerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IRepository & repository) const = 0;
};

}