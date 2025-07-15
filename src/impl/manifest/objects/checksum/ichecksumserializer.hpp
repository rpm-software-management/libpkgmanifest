// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ichecksum.hpp"

#include "impl/common/yaml/iyamlnode.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IChecksumSerializer {
public:
    virtual ~IChecksumSerializer() = default;

    virtual std::unique_ptr<IYamlNode> serialize(const IChecksum & checksum) const = 0;
};

}