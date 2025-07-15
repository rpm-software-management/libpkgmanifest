// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iversion.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IVersionFactory {
public:
    virtual ~IVersionFactory() = default;

    virtual std::unique_ptr<IVersion> create() const = 0;
};

}