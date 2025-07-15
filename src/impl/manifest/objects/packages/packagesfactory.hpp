// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackagesfactory.hpp"

namespace libpkgmanifest::internal::manifest {

class PackagesFactory : public IPackagesFactory {
public:
    virtual std::unique_ptr<IPackages> create() const override;
};

}