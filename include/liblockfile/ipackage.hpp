#pragma once

#include "ichecksum.hpp"

#include <stdint.h>
#include <string>

namespace liblockfile {

class IPackage {
public:
    virtual ~IPackage() = default;

    virtual std::string get_repo_id() const = 0;
    virtual std::string get_url() const = 0; // TODO: return URL object?
    virtual const IChecksum & get_checksum() const = 0;
    virtual uint64_t get_size() const = 0;
    virtual std::string get_nevra() const = 0; // TODO: return NEVRA object?
    virtual std::string get_srpm() const = 0; // TODO: return NEVRA object?
};

}