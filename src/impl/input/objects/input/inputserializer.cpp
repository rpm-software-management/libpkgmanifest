// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "inputserializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

InputSerializer::InputSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IPackagesSerializer> packages_serializer,
    std::unique_ptr<IRepositoriesSerializer> repositories_serializer,
    std::unique_ptr<IVersionSerializer> version_serializer,
    std::unique_ptr<IModulesSerializer> modules_serializer,
    std::unique_ptr<IOptionsSerializer> options_serializer)
    : node_factory(std::move(node_factory)),
      packages_serializer(std::move(packages_serializer)),
      repositories_serializer(std::move(repositories_serializer)),
      version_serializer(std::move(version_serializer)),
      modules_serializer(std::move(modules_serializer)),
      options_serializer(std::move(options_serializer)) {}

std::unique_ptr<IYamlNode> InputSerializer::serialize(const IInput & input) const {
    auto node = node_factory->create();

    auto document_node = node_factory->create();
    document_node->set(input.get_document());

    auto version_node = version_serializer->serialize(input.get_version());
    auto repositories_node = repositories_serializer->serialize(input.get_repositories());
    auto packages_node = packages_serializer->serialize(input.get_packages());

    node->insert("document", std::move(document_node));
    node->insert("version", std::move(version_node));
    node->insert("repositories", std::move(repositories_node));
    node->insert("packages", std::move(packages_node));

    auto modules_node = modules_serializer->serialize(input.get_modules());
    if (modules_node) {
        node->insert("modules", std::move(modules_node));
    }

    auto archs_node = node_factory->create();
    for (auto & arch : input.get_archs()) {
        auto arch_node = node_factory->create();
        arch_node->set(arch);
        archs_node->add(std::move(arch_node));
    }
    node->insert("archs", std::move(archs_node));

    auto options_node = options_serializer->serialize(input.get_options());
    if (options_node) {
        node->insert("options", std::move(options_node));
    }

    return node;
}

}  // namespace libpkgmanifest::internal::input
