#pragma once

#include "irepositoryserializer.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class RepositorySerializer : public IRepositorySerializer {
public:
    RepositorySerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IRepository & repository) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}