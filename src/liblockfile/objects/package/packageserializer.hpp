#pragma once

#include "ipackageserializer.hpp"

#include "liblockfile/objects/checksum/ichecksumserializer.hpp"
#include "liblockfile/yaml/iyamlnodefactory.hpp"

namespace liblockfile {

class PackageSerializer : public IPackageSerializer {
public:
    PackageSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory, 
        std::unique_ptr<IChecksumSerializer> checksum_serializer);

    virtual std::unique_ptr<IYamlNode> serialize(const IPackage & package) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IChecksumSerializer> checksum_serializer;
};

}