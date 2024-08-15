#include "serializerfactory.hpp"
#include "serializer.hpp"

#include "liblockfile/objects/checksum/checksumserializer.hpp"
#include "liblockfile/objects/package/packageserializer.hpp"
#include "liblockfile/objects/packages/packagesserializer.hpp"
#include "liblockfile/objects/lockfile/lockfileserializer.hpp"
#include "liblockfile/objects/version/versionserializer.hpp"
#include "liblockfile/yaml/yamlnodefactory.hpp"
#include "liblockfile/yaml/yamlserializer.hpp"

namespace liblockfile::internal {

std::unique_ptr<ISerializer> SerializerFactory::create() const {
    auto node_factory = std::make_shared<YamlNodeFactory>();

    auto checksum_serializer = std::make_unique<ChecksumSerializer>(node_factory);
    auto package_serializer = std::make_unique<PackageSerializer>(node_factory, std::move(checksum_serializer));
    auto packages_serializer = std::make_unique<PackagesSerializer>(node_factory, std::move(package_serializer));
    auto version_serializer = std::make_unique<VersionSerializer>(node_factory);

    auto lockfile_serializer = std::make_unique<LockFileSerializer>(
        node_factory, 
        std::move(packages_serializer), 
        std::move(version_serializer)
    );

    auto yaml_serializer = std::make_unique<YamlSerializer>();

    return std::make_unique<Serializer>(
        std::move(yaml_serializer), 
        std::move(lockfile_serializer)
    );
}

}