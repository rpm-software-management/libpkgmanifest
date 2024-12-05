#pragma once

#include "libpkgmanifest/manifest/checksum.hpp"

#include <memory>
#include <string>

namespace libpkgmanifest::internal::manifest {

using ChecksumMethod = libpkgmanifest::manifest::ChecksumMethod;

class IChecksum {
public:
    virtual ~IChecksum() = default;

    virtual std::unique_ptr<IChecksum> clone() const = 0;

    virtual ChecksumMethod get_method() const = 0;
    virtual std::string get_digest() const = 0;

    virtual void set_method(ChecksumMethod method) = 0;
    virtual void set_digest(const std::string & digest) = 0;
};

}