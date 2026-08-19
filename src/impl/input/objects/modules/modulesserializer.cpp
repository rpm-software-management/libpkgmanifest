// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "modulesserializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

ModulesSerializer::ModulesSerializer(std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(std::move(node_factory)) {}

std::unique_ptr<IYamlNode> ModulesSerializer::serialize(const IModules & modules) const {
    if (modules.get_enables().empty() && modules.get_disables().empty()) {
        return nullptr;
    }

    auto node = node_factory->create();

    if (!modules.get_enables().empty()) {
        auto enable_node = node_factory->create();
        for (auto & enable : modules.get_enables()) {
            auto item_node = node_factory->create();
            item_node->set(enable);
            enable_node->add(std::move(item_node));
        }
        node->insert("enable", std::move(enable_node));
    }

    if (!modules.get_disables().empty()) {
        auto disable_node = node_factory->create();
        for (auto & disable : modules.get_disables()) {
            auto item_node = node_factory->create();
            item_node->set(disable);
            disable_node->add(std::move(item_node));
        }
        node->insert("disable", std::move(disable_node));
    }

    return node;
}

}  // namespace libpkgmanifest::internal::input
