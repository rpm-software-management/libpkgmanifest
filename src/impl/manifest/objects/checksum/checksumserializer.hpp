#pragma once

#include "ichecksumserializer.hpp"

#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class ChecksumSerializer : public IChecksumSerializer {
public:
    ChecksumSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IChecksum & checksum) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}