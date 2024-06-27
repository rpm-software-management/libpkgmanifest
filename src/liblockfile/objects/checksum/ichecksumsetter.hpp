#pragma once

#include "liblockfile/ichecksum.hpp"

#include <string>

namespace liblockfile {

class IChecksumSetter {
public:
    virtual ~IChecksumSetter() = default;

    virtual void set_method(ChecksumMethod method) = 0;
    virtual void set_digest(const std::string & digest) = 0;
};

}