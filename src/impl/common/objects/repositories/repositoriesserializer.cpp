#include "repositoriesserializer.hpp"

namespace libpkgmanifest::internal::common {

RepositoriesSerializer::RepositoriesSerializer(
    std::shared_ptr<IYamlNodeFactory> node_factory,
    std::unique_ptr<IRepositorySerializer> repository_serializer)
    : node_factory(std::move(node_factory))
    , repository_serializer(std::move(repository_serializer)) {}

std::unique_ptr<IYamlNode> RepositoriesSerializer::serialize(const IRepositories & repositories) const {
    auto node = node_factory->create();

    for (auto & [_, repository] : repositories.get()) {
        node->add(repository_serializer->serialize(*repository));
    }

    return node;
}

}