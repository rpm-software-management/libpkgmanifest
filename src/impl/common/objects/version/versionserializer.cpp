// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "versionserializer.hpp"

#include <format>

namespace libpkgmanifest::internal::common {

VersionSerializer::VersionSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(std::move(node_factory)) {}

std::unique_ptr<IYamlNode> VersionSerializer::serialize(const IVersion & version) const {
    auto node = node_factory->create();
    node->set(std::format("{}.{}.{}", version.get_major(), version.get_minor(), version.get_patch()));
    return node;
}

}