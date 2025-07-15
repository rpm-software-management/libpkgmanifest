// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::common {

class YamlNodeFactory : public IYamlNodeFactory {
public:
    virtual std::unique_ptr<IYamlNodeInternal> create() const override;
};

}