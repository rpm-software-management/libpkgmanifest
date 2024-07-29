#pragma once

#include "liblockfile/checksum.hpp"

#include "liblockfile/objects/checksum/ichecksum.hpp"

namespace liblockfile {

class Checksum::Impl {
public:
    void set(const internal::IChecksum & checksum) {
        this->checksum = &checksum;
    }
private:
    friend Checksum;
    const internal::IChecksum * checksum;
};

}