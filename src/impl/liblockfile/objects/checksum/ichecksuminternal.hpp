#pragma once

#include "ichecksum.hpp"
#include "ichecksumsetter.hpp"

namespace liblockfile::internal {

class IChecksumInternal : public IChecksum, public IChecksumSetter {
};

}