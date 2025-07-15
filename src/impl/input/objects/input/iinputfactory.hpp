// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iinput.hpp"

#include <memory>

namespace libpkgmanifest::internal::input {

class IInputFactory {
public:
    virtual ~IInputFactory() = default;

    virtual std::unique_ptr<IInput> create() const = 0;
};

}