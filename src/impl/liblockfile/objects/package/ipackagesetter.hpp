#pragma once

#include "liblockfile/objects/checksum/ichecksum.hpp"

#include <memory>
#include <stdint.h>
#include <string>

namespace liblockfile::internal {

class IPackageSetter {
public:
    virtual ~IPackageSetter() = default;

    virtual void set_arch(const std::string & arch) = 0;
    virtual void set_repo_id(const std::string & repo_id) = 0;
    virtual void set_url(const std::string & url) = 0;
    virtual void set_checksum(std::unique_ptr<IChecksum> checksum) = 0;
    virtual void set_size(uint64_t size) = 0;
    virtual void set_nevra(const std::string & nevra) = 0;
    virtual void set_srpm(const std::string & srpm) = 0;
};

}