#pragma once

#include "libpkgmanifest/checksum.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal {

class IChecksum {
public:
    virtual ~IChecksum() = default;

    virtual std::unique_ptr<IChecksum> clone() const = 0;

    virtual libpkgmanifest::ChecksumMethod get_method() const = 0;
    virtual std::string get_digest() const = 0;

    virtual void set_method(ChecksumMethod method) = 0;
    virtual void set_digest(const std::string & digest) = 0;
};

}