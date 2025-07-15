// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "libpkgmanifest/input/options.hpp"

#include "api/shared/base_impl.hpp"
#include "impl/input/objects/options/optionsfactory.hpp"

namespace libpkgmanifest::input {

using namespace libpkgmanifest::internal::input;

class Options::Impl : public BaseImpl<IOptions, OptionsFactory> {};

}