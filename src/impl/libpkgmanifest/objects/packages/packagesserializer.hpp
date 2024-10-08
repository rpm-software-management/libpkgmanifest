#pragma once

#include "ipackagesserializer.hpp"

#include "impl/libpkgmanifest/objects/package/ipackageserializer.hpp"
#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

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