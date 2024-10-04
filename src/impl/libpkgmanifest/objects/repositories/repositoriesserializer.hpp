#pragma once

#include "irepositoriesserializer.hpp"

#include "libpkgmanifest/objects/repository/irepositoryserializer.hpp"
#include "libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class RepositoriesSerializer : public IRepositoriesSerializer {
public:
    RepositoriesSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory, 
        std::unique_ptr<IRepositorySerializer> repository_serializer);

    virtual std::unique_ptr<IYamlNode> serialize(const IRepositories & repositories) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IRepositorySerializer> repository_serializer;
};

}