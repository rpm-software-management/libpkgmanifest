#include "manifestserializer.hpp"

namespace libpkgmanifest::internal {

ManifestSerializer::ManifestSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IPackagesSerializer> packages_serializer,
    std::unique_ptr<IVersionSerializer> version_serializer)
    : node_factory(node_factory)
    , packages_serializer(std::move(packages_serializer))
    , version_serializer(std::move(version_serializer)) {}

std::unique_ptr<IYamlNode> ManifestSerializer::serialize(const IManifest & manifest) const {
    auto node = node_factory->create();

    auto document_node = node_factory->create();
    document_node->set(manifest.get_document());

    auto version_node = version_serializer->serialize(manifest.get_version());

    auto packages_node = packages_serializer->serialize(manifest.get_packages());

    auto data_node = node_factory->create();
    data_node->insert("packages", std::move(packages_node));

    node->insert("document", std::move(document_node));
    node->insert("version", std::move(version_node));
    node->insert("data", std::move(data_node));

    return node;
}

}