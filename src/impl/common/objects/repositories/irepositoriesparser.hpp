// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "irepositories.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoriesParser {
public:
    virtual ~IRepositoriesParser() = default;

    virtual std::unique_ptr<IRepositories> parse(const IYamlNode & node) const = 0;
};

}  // namespace libpkgmanifest::internal::common
