#pragma once

#include "ichecksuminternal.hpp"

namespace liblockfile {

class Checksum : IChecksumInternal {
public:
    virtual ChecksumMethod get_method() const override;
    virtual std::string get_digest() const override;

    virtual void set_method(ChecksumMethod method) override;
    virtual void set_digest(const std::string & digest) override;

private:
    ChecksumMethod method;
    std::string digest;
};

}