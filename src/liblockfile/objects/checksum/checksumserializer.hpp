#pragma once

#include "ichecksumserializer.hpp"

#include "liblockfile/yaml/iyamlnodefactory.hpp"

namespace liblockfile {

class ChecksumSerializer : public IChecksumSerializer {
public:
    ChecksumSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IChecksum & checksum) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}