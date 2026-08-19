// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ioptions.hpp"

#include <optional>

namespace libpkgmanifest::internal::input {

class Options : public IOptions {
public:
    virtual std::unique_ptr<IOptions> clone() const override;

    virtual bool has_allow_erasing() const override;
    virtual bool get_allow_erasing() const override;
    virtual void set_allow_erasing(bool allow_erasing) override;

private:
    std::optional<bool> allow_erasing;
};

}  // namespace libpkgmanifest::internal::input
