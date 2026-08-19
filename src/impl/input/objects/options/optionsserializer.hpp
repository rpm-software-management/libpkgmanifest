// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/yaml/iyamlnodefactory.hpp"
#include "ioptionsserializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class OptionsSerializer : public IOptionsSerializer {
public:
    OptionsSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IOptions & options) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}  // namespace libpkgmanifest::internal::input
