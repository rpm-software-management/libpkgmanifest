#pragma once

#include "iversionserializer.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class VersionSerializer : public IVersionSerializer {
public:
    VersionSerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IVersion & version) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}