// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "api/shared/base_impl.hpp"
#include "impl/manifest/objects/module/modulefactory.hpp"
#include "libpkgmanifest/manifest/module.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Module::Impl : public BaseImpl<IModule, ModuleFactory> {};

}  // namespace libpkgmanifest::manifest
