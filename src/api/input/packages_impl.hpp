// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "api/shared/base_impl.hpp"
#include "impl/input/objects/packages/packagesfactory.hpp"
#include "libpkgmanifest/input/packages.hpp"

namespace libpkgmanifest::input {

using namespace libpkgmanifest::internal::input;

class Packages::Impl : public BaseImpl<IPackages, PackagesFactory> {};

}  // namespace libpkgmanifest::input
