// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "ioptions.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IOptionsSerializer {
public:
    virtual ~IOptionsSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IOptions & options) const = 0;
};

}  // namespace libpkgmanifest::internal::input
