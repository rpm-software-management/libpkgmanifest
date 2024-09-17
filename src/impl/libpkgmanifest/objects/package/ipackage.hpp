#pragma once

#include "libpkgmanifest/objects/checksum/ichecksum.hpp"
#include "libpkgmanifest/objects/module/imodule.hpp"

#include <memory>
#include <stdint.h>
#include <string>

namespace libpkgmanifest::internal {

class IPackage {
public:
    virtual ~IPackage() = default;

    virtual std::unique_ptr<IPackage> clone() const = 0;

    virtual std::string get_arch() const = 0;
    virtual std::string get_repo_id() const = 0;
    virtual std::string get_url() const = 0; // TODO: return URL object?
    virtual const IChecksum & get_checksum() const = 0;
    virtual IChecksum & get_checksum() = 0;
    virtual uint64_t get_size() const = 0;
    virtual std::string get_nevra() const = 0; // TODO: return NEVRA object?
    virtual std::string get_srpm() const = 0; // TODO: return NEVRA object?
    virtual const IModule & get_module() const = 0;
    virtual IModule & get_module() = 0;

    virtual void set_arch(const std::string & arch) = 0;
    virtual void set_repo_id(const std::string & repo_id) = 0;
    virtual void set_url(const std::string & url) = 0;
    virtual void set_checksum(std::unique_ptr<IChecksum> checksum) = 0;
    virtual void set_size(uint64_t size) = 0;
    virtual void set_nevra(const std::string & nevra) = 0;
    virtual void set_srpm(const std::string & srpm) = 0;
    virtual void set_module(std::unique_ptr<IModule> module) = 0;
};

}