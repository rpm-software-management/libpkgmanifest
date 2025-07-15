// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imanifest.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

class IManifestFactory {
public:
    virtual ~IManifestFactory() = default;

    virtual std::unique_ptr<IManifest> create() const = 0;
};

}