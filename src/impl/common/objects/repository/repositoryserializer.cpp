#include "repositoryserializer.hpp"

namespace libpkgmanifest::internal::common {

RepositorySerializer::RepositorySerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory)
    : node_factory(node_factory) {}

std::unique_ptr<IYamlNode> RepositorySerializer::serialize(const IRepository & repository) const {
    auto node = node_factory->create();

    auto id_node = node_factory->create();
    id_node->set(repository.get_id());
    node->insert("id", std::move(id_node));

    auto baseurl = repository.get_baseurl();
    if (!baseurl.empty()) {
        auto baseurl_node = node_factory->create();
        baseurl_node->set(baseurl);
        node->insert("baseurl", std::move(baseurl_node));
    }

    auto metalink = repository.get_metalink();
    if (!metalink.empty()) {
        auto metalink_node = node_factory->create();
        metalink_node->set(metalink);
        node->insert("metalink", std::move(metalink_node));
    }

    auto mirrorlist = repository.get_mirrorlist();
    if (!mirrorlist.empty()) {
        auto mirrorlist_node = node_factory->create();
        mirrorlist_node->set(mirrorlist);
        node->insert("mirrorlist", std::move(mirrorlist_node));
    }

    return node;
}

}