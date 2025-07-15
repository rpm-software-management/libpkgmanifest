// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "version.hpp"
#include "versionfactory.hpp"

namespace libpkgmanifest::internal::common {

std::unique_ptr<IVersion> VersionFactory::create() const {
    return std::make_unique<Version>();
}   

}