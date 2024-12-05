#include "manifestserializer.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

ManifestSerializer::ManifestSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IPackagesSerializer> packages_serializer,
    std::unique_ptr<IRepositoriesSerializer> repositories_serializer,
    std::unique_ptr<IVersionSerializer> version_serializer,
    std::shared_ptr<IPackageRepositoryBinder> binder)
    : node_factory(node_factory)
    , packages_serializer(std::move(packages_serializer))
    , repositories_serializer(std::move(repositories_serializer))
    , version_serializer(std::move(version_serializer))
    , binder(binder) {}

std::unique_ptr<IYamlNode> ManifestSerializer::serialize(const IManifest & manifest) const {
    auto & repositories = manifest.get_repositories();
    auto & packages = manifest.get_packages();
    binder->validate(repositories, packages);

    auto node = node_factory->create();

    auto document_node = node_factory->create();
    document_node->set(manifest.get_document());

    auto version_node = version_serializer->serialize(manifest.get_version());

    auto repositories_node = repositories_serializer->serialize(repositories);
    auto packages_node = packages_serializer->serialize(packages);

    auto data_node = node_factory->create();
    data_node->insert("repositories", std::move(repositories_node));
    data_node->insert("packages", std::move(packages_node));

    node->insert("document", std::move(document_node));
    node->insert("version", std::move(version_node));
    node->insert("data", std::move(data_node));

    return node;
}

}