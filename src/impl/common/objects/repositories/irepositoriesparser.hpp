// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "irepositories.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoriesParser {
public:
    virtual ~IRepositoriesParser() = default;

    virtual std::unique_ptr<IRepositories> parse(const IYamlNode & node) const = 0;
};

}