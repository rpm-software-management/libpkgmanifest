// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "yamlnodefactory.hpp"

#include "yamlnode.hpp"

namespace libpkgmanifest::internal::common {

std::unique_ptr<IYamlNodeInternal> YamlNodeFactory::create() const {
    return std::make_unique<YamlNode>();
}

}  // namespace libpkgmanifest::internal::common
