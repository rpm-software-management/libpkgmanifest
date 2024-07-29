#pragma once

#include "liblockfile/checksum.hpp"

#include <string>

namespace liblockfile::internal {

class IChecksum {
public:
    virtual ~IChecksum() = default;

    virtual liblockfile::ChecksumMethod get_method() const = 0;
    virtual std::string get_digest() const = 0;
};

}