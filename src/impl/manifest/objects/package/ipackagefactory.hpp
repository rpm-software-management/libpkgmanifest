// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackage.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

class IPackageFactory {
public:
    virtual ~IPackageFactory() = default;

    virtual std::unique_ptr<IPackage> create() const = 0;
};

}