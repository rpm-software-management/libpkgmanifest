// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imoduleserializer.hpp"

#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class ModuleSerializer : public IModuleSerializer {
public:
    ModuleSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IModule & module) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}