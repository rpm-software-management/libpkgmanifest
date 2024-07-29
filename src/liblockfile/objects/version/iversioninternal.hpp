#pragma once

#include "iversion.hpp"
#include "iversionsetter.hpp"

namespace liblockfile {

class IVersionInternal : public IVersion, public IVersionSetter {
};

}