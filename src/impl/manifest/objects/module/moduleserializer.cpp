// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "moduleserializer.hpp"

#include <format>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

ModuleSerializer::ModuleSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(std::move(node_factory)) {}

std::unique_ptr<IYamlNode> ModuleSerializer::serialize(const IModule & module) const {
    auto node = node_factory->create();
    node->set(module.get_name() + ":" + module.get_stream());
    return node;
}

}