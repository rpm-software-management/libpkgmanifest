#pragma once

#include "ilockfileserializer.hpp"

#include "liblockfile/objects/packages/ipackagesserializer.hpp"
#include "liblockfile/objects/version/iversionserializer.hpp"
#include "liblockfile/yaml/iyamlnodefactory.hpp"

namespace liblockfile::internal {

class LockFileSerializer : public ILockFileSerializer {
public:
    LockFileSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory, 
        std::unique_ptr<IPackagesSerializer> packages_serializer,
        std::unique_ptr<IVersionSerializer> version_serializer);

    virtual std::unique_ptr<IYamlNode> serialize(const ILockFile & file) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IPackagesSerializer> packages_serializer;
    std::unique_ptr<IVersionSerializer> version_serializer;
};

}