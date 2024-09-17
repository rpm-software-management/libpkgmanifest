#include "moduleserializer.hpp"

#include <format>

namespace libpkgmanifest::internal {

ModuleSerializer::ModuleSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(node_factory) {}

std::unique_ptr<IYamlNode> ModuleSerializer::serialize(const IModule & module) const {
    auto node = node_factory->create();
    node->set(module.get_name() + ":" + module.get_stream());
    return node;
}

}