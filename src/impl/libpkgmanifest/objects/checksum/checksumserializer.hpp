#pragma once

#include "ichecksumserializer.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class ChecksumSerializer : public IChecksumSerializer {
public:
    ChecksumSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IChecksum & checksum) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}