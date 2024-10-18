#pragma once

#include "iprototypeinfileconverter.hpp"

#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

constexpr const char * INPUT_PROTOTYPE_DOCUMENT_ID = "rpm-package-input-prototype";

constexpr int INPUT_PROTOTYPE_DOCUMENT_VERSION_MAJOR = 0;
constexpr int INPUT_PROTOTYPE_DOCUMENT_VERSION_MINOR = 0;
constexpr int INPUT_PROTOTYPE_DOCUMENT_VERSION_PATCH = 1;

class PrototypeInFileConverter : public IPrototypeInFileConverter {
public:
    PrototypeInFileConverter(std::shared_ptr<IYamlNodeFactory> node_factory);

    virtual std::unique_ptr<IYamlNode> convert(const IYamlNode & node) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
};

}