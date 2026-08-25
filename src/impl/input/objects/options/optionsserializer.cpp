// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "optionsserializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

OptionsSerializer::OptionsSerializer(std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(std::move(node_factory)) {}

std::unique_ptr<IYamlNode> OptionsSerializer::serialize(const IOptions & options) const {
    if (!options.has_allow_erasing()) {
        return nullptr;
    }

    auto node = node_factory->create();

    auto allow_erasing_node = node_factory->create();
    allow_erasing_node->set(options.get_allow_erasing());
    node->insert("allow_erasing", std::move(allow_erasing_node));

    return node;
}

}  // namespace libpkgmanifest::internal::input
