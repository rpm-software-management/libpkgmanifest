#include "yamlnode.hpp"

namespace libpkgmanifest::internal {

YamlUnknownKeyError::YamlUnknownKeyError(const std::string & message)
    : std::runtime_error(message) {}

YamlInvalidValueConversionError::YamlInvalidValueConversionError(const std::string & message)
    : std::runtime_error(message) {}

YamlNode::YamlNode() {}

YamlNode::YamlNode(const YAML::Node & node)
    : node(node) {}

bool YamlNode::has(const std::string & key) const {
    return node.IsMap() && bool(node[key]);
}

std::unique_ptr<IYamlNode> YamlNode::get(const std::string & key) const {
    auto inner_node = node[key];
    if (!inner_node) {
        throw YamlUnknownKeyError("Unknown key: " + key);
    }
    return std::unique_ptr<IYamlNode>(new YamlNode(std::move(inner_node)));
}

std::string YamlNode::as_string() const {
    return as<std::string>();
}

bool YamlNode::as_bool() const {
    return as<bool>();
}

int YamlNode::as_int() const {
    return as<int>();
}

unsigned YamlNode::as_uint() const {
    return as<unsigned>();
}

uint64_t YamlNode::as_uint64() const {
    return as<uint64_t>();
}

std::vector<std::unique_ptr<IYamlNode>> YamlNode::as_list() const {
    std::vector<std::unique_ptr<IYamlNode>> nodes;
    for (std::size_t i = 0; i < node.size(); i++) {
        nodes.push_back(std::unique_ptr<YamlNode>(new YamlNode(node[i])));
    }
    return nodes;
}

std::map<std::string, std::unique_ptr<IYamlNode>> YamlNode::as_map() const {
    std::map<std::string, std::unique_ptr<IYamlNode>> nodes;
    for (auto it = node.begin(); it != node.end(); it++) {
        nodes.insert({it->first.as<std::string>(), std::unique_ptr<IYamlNode>(new YamlNode(it->second))});
    }
    return nodes;
}

void YamlNode::set(const std::string & value) {
    node = value;
}

void YamlNode::set(const char * value) {
    node = value;
}

void YamlNode::set(bool value) {
    node = value;
}

void YamlNode::set(int value) {
    node = value;
}

void YamlNode::set(unsigned value) {
    node = value;
}

void YamlNode::set(uint64_t value) {
    node = value;
}

void YamlNode::add(std::unique_ptr<IYamlNode> value) {
    node.push_back(static_cast<YamlNode*>(value.get())->node);
}

void YamlNode::insert(const std::string & key, std::unique_ptr<IYamlNode> value) {
    node[key] = static_cast<YamlNode*>(value.get())->node;
}

const YAML::Node & YamlNode::get_node() const {
    return node;
}

}