#pragma once

#include "iyamlnode.hpp"
#include "iyamlnodesetter.hpp"

namespace liblockfile::internal {

class IYamlNodeInternal : public IYamlNode, public IYamlNodeSetter {
};

}