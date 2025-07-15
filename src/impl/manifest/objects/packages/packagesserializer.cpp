// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "packagesserializer.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

PackagesSerializer::PackagesSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IPackageSerializer> package_serializer)
    : node_factory(std::move(node_factory))
    , package_serializer(std::move(package_serializer)) {}

std::unique_ptr<IYamlNode> PackagesSerializer::serialize(const IPackages & packages) const {
    auto node = node_factory->create();

    for (const auto & arch : packages.get_archs()) {
        auto arch_node = node_factory->create();
        for (const auto & package : packages.get(arch)) {
            arch_node->add(package_serializer->serialize(*package));
        }
        node->insert(arch, std::move(arch_node));
    }

    return node;
}

}