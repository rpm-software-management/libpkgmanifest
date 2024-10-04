#include "repositoryserializer.hpp"

namespace libpkgmanifest::internal {

RepositorySerializer::RepositorySerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(node_factory) {}

std::unique_ptr<IYamlNode> RepositorySerializer::serialize(const IRepository & repository) const {
    auto node = node_factory->create();

    auto id_node = node_factory->create();
    id_node->set(repository.get_id());
    node->insert("id", std::move(id_node));

    auto url_node = node_factory->create();
    url_node->set(repository.get_url());
    node->insert("url", std::move(url_node));

    return node;
}

}