// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "nevra.hpp"
#include "nevrafactory.hpp"

namespace libpkgmanifest::internal::manifest {

std::unique_ptr<INevra> NevraFactory::create() const {
    return std::make_unique<Nevra>();
}   

}