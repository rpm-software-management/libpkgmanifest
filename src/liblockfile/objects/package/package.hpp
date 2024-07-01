#pragma once

#include "ipackageinternal.hpp"

#include <memory>

namespace liblockfile {

class Package : public IPackageInternal {
public:
    Package();

    virtual std::string get_arch() const override;
    virtual std::string get_repo_id() const override;
    virtual std::string get_url() const override;
    virtual const IChecksum & get_checksum() const override;
    virtual uint64_t get_size() const override;
    virtual std::string get_nevra() const override;
    virtual std::string get_srpm() const override;

    virtual void set_arch(const std::string & arch) override;
    virtual void set_repo_id(const std::string & repo_id) override;
    virtual void set_url(const std::string & url) override;
    virtual void set_checksum(std::unique_ptr<IChecksum> checksum) override;
    virtual void set_size(uint64_t size) override;
    virtual void set_nevra(const std::string & nevra) override;
    virtual void set_srpm(const std::string & srpm) override;

private:
    std::string arch;
    std::string repo_id;
    std::string url;
    std::unique_ptr<IChecksum> checksum;
    uint64_t size;
    std::string nevra;
    std::string srpm;
};

}