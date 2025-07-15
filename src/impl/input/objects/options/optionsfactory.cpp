// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "options.hpp"
#include "optionsfactory.hpp"

namespace libpkgmanifest::internal::input {

std::unique_ptr<IOptions> OptionsFactory::create() const {
    return std::make_unique<Options>();
}   

}