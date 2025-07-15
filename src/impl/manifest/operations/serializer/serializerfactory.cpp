// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "serializerfactory.hpp"
#include "serializer.hpp"

#include "impl/common/objects/repository/repositoryserializer.hpp"
#include "impl/common/objects/repositories/repositoriesserializer.hpp"
#include "impl/common/objects/version/versionserializer.hpp"
#include "impl/common/yaml/yamlnodefactory.hpp"
#include "impl/common/yaml/yamlserializer.hpp"
#include "impl/manifest/objects/checksum/checksumserializer.hpp"
#include "impl/manifest/objects/module/moduleserializer.hpp"
#include "impl/manifest/objects/package/packageserializer.hpp"
#include "impl/manifest/objects/packages/packagesserializer.hpp"
#include "impl/manifest/objects/manifest/manifestserializer.hpp"
#include "impl/manifest/operations/packagerepositorybinder/packagerepositorybinder.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

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