// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "versionfactory.hpp"

#include "version.hpp"

namespace libpkgmanifest::internal::common {

std::unique_ptr<IVersion> VersionFactory::create() const {
    return std::make_unique<Version>();
}

}  // namespace libpkgmanifest::internal::common
