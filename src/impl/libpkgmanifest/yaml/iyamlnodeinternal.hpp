#pragma once

#include "iyamlnode.hpp"
#include "iyamlnodesetter.hpp"

namespace libpkgmanifest::internal {

class IYamlNodeInternal : public IYamlNode, public IYamlNodeSetter {
};

}