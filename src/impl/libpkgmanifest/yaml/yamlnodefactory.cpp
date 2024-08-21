#include "yamlnode.hpp"
#include "yamlnodefactory.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IYamlNodeInternal> YamlNodeFactory::create() const {
    return std::unique_ptr<IYamlNodeInternal>(new YamlNode());
}   

}