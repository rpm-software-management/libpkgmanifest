// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackages.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

class IPackagesFactory {
public:
    virtual ~IPackagesFactory() = default;

    virtual std::unique_ptr<IPackages> create() const = 0;
};

}