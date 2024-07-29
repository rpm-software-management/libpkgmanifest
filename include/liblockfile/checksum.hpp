#pragma once

#include <string>

namespace liblockfile {

enum class ChecksumMethod {
    SHA256, SHA512, MD5, CRC32, CRC64
};

class Checksum {
public:
    ChecksumMethod get_method() const;
    std::string get_digest() const;
};

}