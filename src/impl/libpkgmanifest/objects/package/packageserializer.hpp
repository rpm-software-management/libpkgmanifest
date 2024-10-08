#pragma once

#include "ipackageserializer.hpp"

#include "impl/libpkgmanifest/objects/checksum/ichecksumserializer.hpp"
#include "impl/libpkgmanifest/objects/module/imoduleserializer.hpp"
#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class PackageSerializer : public IPackageSerializer {
public:
    PackageSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory, 
        std::unique_ptr<IChecksumSerializer> checksum_serializer,
        std::unique_ptr<IModuleSerializer> module_serializer);

    virtual std::unique_ptr<IYamlNode> serialize(const IPackage & package) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IChecksumSerializer> checksum_serializer;
    std::unique_ptr<IModuleSerializer> module_serializer;
};

}