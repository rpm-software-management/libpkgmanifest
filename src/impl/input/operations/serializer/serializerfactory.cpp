// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "serializerfactory.hpp"

#include "impl/common/objects/repositories/repositoriesserializer.hpp"
#include "impl/common/objects/repository/repositoryserializer.hpp"
#include "impl/common/objects/version/versionserializer.hpp"
#include "impl/common/yaml/yamlnodefactory.hpp"
#include "impl/common/yaml/yamlserializer.hpp"
#include "impl/input/objects/input/inputserializer.hpp"
#include "impl/input/objects/modules/modulesserializer.hpp"
#include "impl/input/objects/options/optionsserializer.hpp"
#include "impl/input/objects/packages/packagesserializer.hpp"
#include "serializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

std::unique_ptr<ISerializer> SerializerFactory::create() const {
    auto node_factory = std::make_shared<YamlNodeFactory>();

    auto packages_serializer = std::make_unique<PackagesSerializer>(node_factory);
    auto modules_serializer = std::make_unique<ModulesSerializer>(node_factory);
    auto options_serializer = std::make_unique<OptionsSerializer>(node_factory);

    auto repository_serializer = std::make_unique<RepositorySerializer>(node_factory);
    auto repositories_serializer =
        std::make_unique<RepositoriesSerializer>(node_factory, std::move(repository_serializer));

    auto version_serializer = std::make_unique<VersionSerializer>(node_factory);

    auto input_serializer = std::make_unique<InputSerializer>(
        node_factory,
        std::move(packages_serializer),
        std::move(repositories_serializer),
        std::move(version_serializer),
        std::move(modules_serializer),
        std::move(options_serializer));

    auto yaml_serializer = std::make_unique<YamlSerializer>();

    return std::make_unique<Serializer>(std::move(yaml_serializer), std::move(input_serializer));
}

}  // namespace libpkgmanifest::internal::input
