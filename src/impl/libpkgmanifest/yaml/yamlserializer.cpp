#include "yamlnode.hpp"
#include "yamlserializer.hpp"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace libpkgmanifest::internal {

FileOutputError::FileOutputError(const std::string & message)
    : std::runtime_error(message) {}

std::string YamlSerializer::to_string(const IYamlNode & node) const {
    return dynamic_cast<const YamlNode *>(&node)->get_node().as<std::string>();
}

void YamlSerializer::to_file(const IYamlNode & node, const std::string & path) const {
    std::ofstream file_stream;
    file_stream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    try {
        file_stream.open(path);
        file_stream << dynamic_cast<const YamlNode *>(&node)->get_node();
    } catch (std::ofstream::failure & ex) {
        throw FileOutputError(ex.what());
    }
}

}
