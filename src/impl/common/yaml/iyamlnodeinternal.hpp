// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iyamlnode.hpp"
#include "iyamlnodesetter.hpp"

namespace libpkgmanifest::internal::common {

class IYamlNodeInternal : public IYamlNode, public IYamlNodeSetter {
};

}