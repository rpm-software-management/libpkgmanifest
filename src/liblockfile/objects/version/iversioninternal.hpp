#pragma once

#include "iversionsetter.hpp"

#include "liblockfile/iversion.hpp"

namespace liblockfile {

class IVersionInternal : public IVersion, public IVersionSetter {
};

}