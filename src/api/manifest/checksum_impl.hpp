// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "api/shared/base_impl.hpp"
#include "impl/manifest/objects/checksum/checksumfactory.hpp"
#include "libpkgmanifest/manifest/checksum.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Checksum::Impl : public BaseImpl<IChecksum, ChecksumFactory> {};

}  // namespace libpkgmanifest::manifest
