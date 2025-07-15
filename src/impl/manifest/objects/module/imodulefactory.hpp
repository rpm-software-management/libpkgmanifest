// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imodule.hpp"

#include <memory>

namespace libpkgmanifest::internal::manifest {

class IModuleFactory {
public:
    virtual ~IModuleFactory() = default;

    virtual std::unique_ptr<IModule> create() const = 0;
};

}