// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imodulesserializer.hpp"
#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class ModulesSerializer : public IModulesSerializer {
public:
    ModulesSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IModules & modules) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}  // namespace libpkgmanifest::internal::input
