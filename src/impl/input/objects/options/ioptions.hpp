// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::internal::input {

class IOptions {
public:
    virtual ~IOptions() = default;

    virtual std::unique_ptr<IOptions> clone() const = 0;

    virtual bool get_allow_erasing() const = 0;
    virtual void set_allow_erasing(bool allow_erasing) = 0;
};

}