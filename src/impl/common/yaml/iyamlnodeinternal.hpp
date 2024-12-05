#pragma once

#include "iyamlnode.hpp"
#include "iyamlnodesetter.hpp"

namespace libpkgmanifest::internal::common {

class IYamlNodeInternal : public IYamlNode, public IYamlNodeSetter {
};

}