// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "packagesserializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

PackagesSerializer::PackagesSerializer(std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(std::move(node_factory)) {}

std::unique_ptr<IYamlNode> PackagesSerializer::serialize(const IPackages & packages) const {
    auto node = node_factory->create();

    auto install_node = node_factory->create();
    for (auto & install : packages.get_installs()) {
        auto item_node = node_factory->create();
        item_node->set(install);
        install_node->add(std::move(item_node));
    }
    node->insert("install", std::move(install_node));

    if (!packages.get_reinstalls().empty()) {
        auto reinstall_node = node_factory->create();
        for (auto & reinstall : packages.get_reinstalls()) {
            auto item_node = node_factory->create();
            item_node->set(reinstall);
            reinstall_node->add(std::move(item_node));
        }
        node->insert("reinstall", std::move(reinstall_node));
    }

    return node;
}

}  // namespace libpkgmanifest::internal::input
