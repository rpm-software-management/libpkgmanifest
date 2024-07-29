#include "yamlnode.hpp"
#include "yamlserializer.hpp"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace liblockfile::internal {

FileOutputError::FileOutputError(const std::string & message)
    : std::runtime_error(message) {}

std::string YamlSerializer::to_string(const IYamlNode & node) const {
    return dynamic_cast<const YamlNode *>(&node)->get_node().as<std::string>();
}

void YamlSerializer::to_file(const IYamlNode & node, const std::string & path) const {
    std::ofstream file_stream(path);
    try {
        file_stream << dynamic_cast<const YamlNode *>(&node)->get_node();
    } catch (std::ofstream::failure & ex) {
        throw FileOutputError(ex.what());
    }
}

}
