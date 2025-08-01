// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "checksum.hpp"
#include "checksumfactory.hpp"

namespace libpkgmanifest::internal::manifest {

std::unique_ptr<IChecksum> ChecksumFactory::create() const {
    return std::make_unique<Checksum>();
}   

}