#include "packageserializer.hpp"

namespace libpkgmanifest::internal {

PackageSerializer::PackageSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IChecksumSerializer> checksum_serializer,
    std::unique_ptr<IModuleSerializer> module_serializer)
    : node_factory(node_factory)
    , checksum_serializer(std::move(checksum_serializer))
    , module_serializer(std::move(module_serializer)) {}

std::unique_ptr<IYamlNode> PackageSerializer::serialize(const IPackage & package) const {
    auto node = node_factory->create();

    auto repo_id = package.get_repo_id();
    if (!repo_id.empty()) {
        auto repoid_node = node_factory->create();
        repoid_node->set(repo_id);
        node->insert("repoid", std::move(repoid_node));
    }

    auto url = package.get_url();
    if (!url.empty()) {
        auto url_node = node_factory->create();
        url_node->set(url);
        node->insert("url", std::move(url_node));
    }

    node->insert("checksum", checksum_serializer->serialize(package.get_checksum()));

    auto size_node = node_factory->create();
    size_node->set(package.get_size());
    node->insert("size", std::move(size_node));

    auto nevra_node = node_factory->create();
    nevra_node->set(package.get_nevra());
    node->insert("nevra", std::move(nevra_node));

    auto srpm = package.get_srpm();
    if (!srpm.empty()) {
        auto srpm_node = node_factory->create();
        srpm_node->set(srpm);
        node->insert("srpm", std::move(srpm_node));
    }

    auto & module = package.get_module();
    if (!module.get_name().empty()) {
        node->insert("module", module_serializer->serialize(module));
    }

    return node;
}

}