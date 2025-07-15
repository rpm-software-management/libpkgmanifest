// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imodules.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

class IModulesFactory {
public:
    virtual ~IModulesFactory() = default;

    virtual std::unique_ptr<IModules> create() const = 0;
};

}