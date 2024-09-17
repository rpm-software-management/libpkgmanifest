#pragma once

#include "imoduleserializer.hpp"

#include "libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class ModuleSerializer : public IModuleSerializer {
public:
    ModuleSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IModule & module) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}