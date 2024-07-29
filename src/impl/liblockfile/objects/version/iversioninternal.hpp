#pragma once

#include "iversion.hpp"
#include "iversionsetter.hpp"

namespace liblockfile::internal {

class IVersionInternal : public IVersion, public IVersionSetter {
};

}