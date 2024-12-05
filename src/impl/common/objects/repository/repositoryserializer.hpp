#pragma once

#include "irepositoryserializer.hpp"

#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::common {

class RepositorySerializer : public IRepositorySerializer {
public:
    RepositorySerializer(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> serialize(const IRepository & repository) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}