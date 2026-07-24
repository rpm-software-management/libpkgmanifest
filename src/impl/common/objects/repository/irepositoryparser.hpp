// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "irepository.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoryParser {
public:
    virtual ~IRepositoryParser() = default;

    virtual std::unique_ptr<IRepository> parse(const IYamlNode & node) const = 0;
};

}  // namespace libpkgmanifest::internal::common
