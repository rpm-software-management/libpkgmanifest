#pragma once

#include "ipackagesserializer.hpp"

#include "impl/common/yaml/iyamlnodefactory.hpp"
#include "impl/manifest/objects/package/ipackageserializer.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

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