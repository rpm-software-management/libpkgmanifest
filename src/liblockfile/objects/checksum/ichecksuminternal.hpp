#pragma once

#include "ichecksumsetter.hpp"

#include "liblockfile/ichecksum.hpp"

namespace liblockfile {

class IChecksumInternal : IChecksum, IChecksumSetter {
};

}