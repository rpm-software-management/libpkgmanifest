// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ichecksum.hpp"

namespace libpkgmanifest::internal::manifest {

using ChecksumMethod = libpkgmanifest::manifest::ChecksumMethod;

class Checksum : public IChecksum {
public:
    Checksum();

    virtual std::unique_ptr<IChecksum> clone() const override;

    virtual ChecksumMethod get_method() const override;
    virtual std::string get_digest() const override;

    virtual void set_method(ChecksumMethod method) override;
    virtual void set_digest(const std::string & digest) override;

private:
    ChecksumMethod method;
    std::string digest;
};

}