// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "modulefactory.hpp"

#include "module.hpp"

namespace libpkgmanifest::internal::manifest {

std::unique_ptr<IModule> ModuleFactory::create() const {
    return std::make_unique<Module>();
}

}  // namespace libpkgmanifest::internal::manifest
