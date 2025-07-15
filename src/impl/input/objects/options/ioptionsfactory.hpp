// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ioptions.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

class IOptionsFactory {
public:
    virtual ~IOptionsFactory() = default;

    virtual std::unique_ptr<IOptions> create() const = 0;
};

}