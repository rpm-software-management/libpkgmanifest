#pragma once

#include "ipackagesserializer.hpp"

#include "liblockfile/objects/package/ipackageserializer.hpp"
#include "liblockfile/yaml/iyamlnodefactory.hpp"

namespace liblockfile {

class PackagesSerializer : public IPackagesSerializer {
public:
    PackagesSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory, 
        std::unique_ptr<IPackageSerializer> package_serializer);

    virtual std::unique_ptr<IYamlNode> serialize(const IPackages & packages) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IPackageSerializer> package_serializer;
};

}