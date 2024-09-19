#pragma once

#include "ipackage.hpp"

namespace libpkgmanifest::internal {

class Package : public IPackage {
public:
    Package();
    Package(const Package & other);

    virtual std::unique_ptr<IPackage> clone() const override;

    virtual std::string get_repo_id() const override;
    virtual std::string get_url() const override;
    virtual uint64_t get_size() const override;
    virtual const IChecksum & get_checksum() const override;
    virtual IChecksum & get_checksum() override;
    virtual const INevra & get_nevra() const override;
    virtual INevra & get_nevra() override;
    virtual const INevra & get_srpm() const override;
    virtual INevra & get_srpm() override;
    virtual const IModule & get_module() const override;
    virtual IModule & get_module() override;

    virtual void set_repo_id(const std::string & repo_id) override;
    virtual void set_url(const std::string & url) override;
    virtual void set_checksum(std::unique_ptr<IChecksum> checksum) override;
    virtual void set_size(uint64_t size) override;
    virtual void set_nevra(std::unique_ptr<INevra> nevra) override;
    virtual void set_srpm(std::unique_ptr<INevra> srpm) override;
    virtual void set_module(std::unique_ptr<IModule> module) override;

private:
    std::string repo_id;
    std::string url;
    uint64_t size;
    std::unique_ptr<IChecksum> checksum;
    std::unique_ptr<INevra> nevra;
    std::unique_ptr<INevra> srpm;
    std::unique_ptr<IModule> module;
};

}