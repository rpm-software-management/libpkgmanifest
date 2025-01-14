#include "yamlnode.hpp"
#include "yamlnodefactory.hpp"

namespace libpkgmanifest::internal::common {

std::unique_ptr<IYamlNodeInternal> YamlNodeFactory::create() const {
    return std::make_unique<YamlNode>();
}   

}