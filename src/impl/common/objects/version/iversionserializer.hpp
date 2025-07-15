// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iversion.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IVersionSerializer {
public:
    virtual ~IVersionSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IVersion & version) const = 0;
};

}