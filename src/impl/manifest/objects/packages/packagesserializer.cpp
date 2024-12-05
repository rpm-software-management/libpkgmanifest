#include "packagesserializer.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

PackagesSerializer::PackagesSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IPackageSerializer> package_serializer)
    : node_factory(node_factory)
    , package_serializer(std::move(package_serializer)) {}

std::unique_ptr<IYamlNode> PackagesSerializer::serialize(const IPackages & packages) const {
    auto node = node_factory->create();

    for (auto & [arch, packages] : packages.get()) {
        auto arch_node = node_factory->create();
        for (auto & package : packages) {
            arch_node->add(package_serializer->serialize(*package));
        }
        node->insert(arch, std::move(arch_node));
    }

    return node;
}

}