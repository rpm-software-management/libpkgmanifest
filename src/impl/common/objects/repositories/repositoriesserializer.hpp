#pragma once

#include "irepositoriesserializer.hpp"

#include "impl/common/objects/repository/irepositoryserializer.hpp"
#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::common {

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