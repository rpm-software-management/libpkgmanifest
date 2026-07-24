// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "api/shared/base_impl.hpp"
#include "impl/manifest/objects/nevra/nevrafactory.hpp"
#include "libpkgmanifest/manifest/nevra.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Nevra::Impl : public BaseImpl<INevra, NevraFactory> {};

}  // namespace libpkgmanifest::manifest
