// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "yamlnode.hpp"
#include "yamlserializer.hpp"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace libpkgmanifest::internal::common {

FileOutputError::FileOutputError(const std::string & message)
    : std::runtime_error(message) {}

std::string YamlSerializer::to_string(const IYamlNode & node) const {
    auto * yaml_node = dynamic_cast<const YamlNode *>(&node);
    if (!yaml_node) {
        throw std::runtime_error("Node is not an instance of YamlNode");
    }
    return yaml_node->get_node().as<std::string>();
}

void YamlSerializer::to_file(const IYamlNode & node, const std::string & path) const {
    auto * yaml_node = dynamic_cast<const YamlNode *>(&node);
    if (!yaml_node) {
        throw std::runtime_error("Node is not an instance of YamlNode");
    }

    std::ofstream file_stream;
    file_stream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    try {
        file_stream.open(path);
        file_stream << yaml_node->get_node();
    } catch (std::ofstream::failure & ex) {
        throw FileOutputError(ex.what());
    }
}

}
