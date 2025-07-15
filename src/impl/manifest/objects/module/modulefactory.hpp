// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imodulefactory.hpp"

namespace libpkgmanifest::internal::manifest {

class ModuleFactory : public IModuleFactory {
public:
    virtual std::unique_ptr<IModule> create() const override;
};

}