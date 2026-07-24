// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "packagesfactory.hpp"

#include "packages.hpp"

namespace libpkgmanifest::internal::input {

std::unique_ptr<IPackages> PackagesFactory::create() const {
    return std::make_unique<Packages>();
}

}  // namespace libpkgmanifest::internal::input
