#include "serializerfactory.hpp"
#include "serializer.hpp"

#include "libpkgmanifest/objects/checksum/checksumserializer.hpp"
#include "libpkgmanifest/objects/module/moduleserializer.hpp"
#include "libpkgmanifest/objects/package/packageserializer.hpp"
#include "libpkgmanifest/objects/packages/packagesserializer.hpp"
#include "libpkgmanifest/objects/manifest/manifestserializer.hpp"
#include "libpkgmanifest/objects/version/versionserializer.hpp"
#include "libpkgmanifest/yaml/yamlnodefactory.hpp"
#include "libpkgmanifest/yaml/yamlserializer.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<ISerializer> SerializerFactory::create() const {
    auto node_factory = std::make_shared<YamlNodeFactory>();

    auto checksum_serializer = std::make_unique<ChecksumSerializer>(node_factory);
    auto module_serializer = std::make_unique<ModuleSerializer>(node_factory);

    auto package_serializer = std::make_unique<PackageSerializer>(
        node_factory, 
        std::move(checksum_serializer), 
        std::move(module_serializer)
    );

    auto packages_serializer = std::make_unique<PackagesSerializer>(node_factory, std::move(package_serializer));
    auto version_serializer = std::make_unique<VersionSerializer>(node_factory);

    auto manifest_serializer = std::make_unique<ManifestSerializer>(
        node_factory, 
        std::move(packages_serializer), 
        std::move(version_serializer)
    );

    auto yaml_serializer = std::make_unique<YamlSerializer>();

    return std::make_unique<Serializer>(
        std::move(yaml_serializer), 
        std::move(manifest_serializer)
    );
}

}