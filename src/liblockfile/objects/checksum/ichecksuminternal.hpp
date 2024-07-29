#pragma once

#include "ichecksum.hpp"
#include "ichecksumsetter.hpp"

namespace liblockfile {

class IChecksumInternal : public IChecksum, public IChecksumSetter {
};

}