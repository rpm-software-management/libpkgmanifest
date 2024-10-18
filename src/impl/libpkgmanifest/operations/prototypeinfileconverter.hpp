#pragma once

#include "iprototypeinfileconverter.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class PrototypeInFileConverter : public IPrototypeInFileConverter {
public:
    PrototypeInFileConverter(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> convert(const IYamlNode & node) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}