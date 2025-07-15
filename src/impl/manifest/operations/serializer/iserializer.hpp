// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/manifest/objects/manifest/imanifest.hpp"

#include <string>

namespace libpkgmanifest::internal::manifest {

class ISerializer {
public:
    virtual ~ISerializer() = default;

    virtual void serialize_manifest(const IManifest & manifest, const std::string & path) const = 0;
};

}