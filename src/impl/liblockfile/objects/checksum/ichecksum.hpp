#pragma once

#include <string>

namespace liblockfile::internal {

enum class ChecksumMethod {
    SHA256, SHA512, MD5, CRC32, CRC64
};

class IChecksum {
public:
    virtual ~IChecksum() = default;

    virtual ChecksumMethod get_method() const = 0;
    virtual std::string get_digest() const = 0;
};

}