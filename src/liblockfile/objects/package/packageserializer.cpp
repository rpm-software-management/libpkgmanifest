#include "packageserializer.hpp"

namespace liblockfile {

PackageSerializer::PackageSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IChecksumSerializer> checksum_serializer)
    : node_factory(node_factory)
    , checksum_serializer(std::move(checksum_serializer)) {}

std::unique_ptr<IYamlNode> PackageSerializer::serialize(const IPackage & package) const {
    auto node = node_factory->create();

    auto repoid_node = node_factory->create();
    repoid_node->set(package.get_repo_id());

    auto url_node = node_factory->create();
    url_node->set(package.get_url());

    auto checksum_node = checksum_serializer->serialize(package.get_checksum());

    auto size_node = node_factory->create();
    size_node->set(package.get_size());

    auto nevra_node = node_factory->create();
    nevra_node->set(package.get_nevra());

    auto srpm_node = node_factory->create();
    srpm_node->set(package.get_srpm());

    node->insert("repoid", std::move(repoid_node));
    node->insert("url", std::move(url_node));
    node->insert("checksum", std::move(checksum_node));
    node->insert("size", std::move(size_node));
    node->insert("nevra", std::move(nevra_node));
    node->insert("srpm", std::move(srpm_node));

    return node;
}

}