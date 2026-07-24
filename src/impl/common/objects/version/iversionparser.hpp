// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnode.hpp"
#include "iversion.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IVersionParser {
public:
    virtual ~IVersionParser() = default;

    virtual std::unique_ptr<IVersion> parse(const IYamlNode & node) const = 0;
};

}  // namespace libpkgmanifest::internal::common
