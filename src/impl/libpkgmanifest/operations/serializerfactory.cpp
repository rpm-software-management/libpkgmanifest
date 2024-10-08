#include "serializerfactory.hpp"
#include "serializer.hpp"

#include "impl/libpkgmanifest/objects/checksum/checksumserializer.hpp"
#include "impl/libpkgmanifest/objects/module/moduleserializer.hpp"
#include "impl/libpkgmanifest/objects/package/packageserializer.hpp"
#include "impl/libpkgmanifest/objects/packages/packagesserializer.hpp"
#include "impl/libpkgmanifest/objects/repository/repositoryserializer.hpp"
#include "impl/libpkgmanifest/objects/repositories/repositoriesserializer.hpp"
#include "impl/libpkgmanifest/objects/manifest/manifestserializer.hpp"
#include "impl/libpkgmanifest/objects/version/versionserializer.hpp"
#include "impl/libpkgmanifest/operations/packagerepositorybinder.hpp"
#include "impl/libpkgmanifest/yaml/yamlnodefactory.hpp"
#include "impl/libpkgmanifest/yaml/yamlserializer.hpp"

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

    auto repository_serializer = std::make_unique<RepositorySerializer>(node_factory);
    auto repositories_serializer = std::make_unique<RepositoriesSerializer>(node_factory, std::move(repository_serializer));

    auto version_serializer = std::make_unique<VersionSerializer>(node_factory);

    auto binder = std::make_shared<PackageRepositoryBinder>();

    auto manifest_serializer = std::make_unique<ManifestSerializer>(
        node_factory,
        std::move(packages_serializer),
        std::move(repositories_serializer),
        std::move(version_serializer),
        binder
    );

    auto yaml_serializer = std::make_unique<YamlSerializer>();

    return std::make_unique<Serializer>(
        std::move(yaml_serializer), 
        std::move(manifest_serializer)
    );
}

}