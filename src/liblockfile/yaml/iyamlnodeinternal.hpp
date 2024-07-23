#pragma once

#include "iyamlnode.hpp"
#include "iyamlnodesetter.hpp"

namespace liblockfile {

class IYamlNodeInternal : public IYamlNode, public IYamlNodeSetter {
};

}