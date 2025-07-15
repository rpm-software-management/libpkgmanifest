// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackage.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

constexpr const char * ARCH_PLACEHOLDER = "$arch";

class PackageRepositoryNotAttachedError : public std::runtime_error {
public:
    PackageRepositoryNotAttachedError(const std::string & message);
};

class Package : public IPackage {
public:
    Package();
    Package(const Package & other);

    virtual std::unique_ptr<IPackage> clone() const override;

    virtual std::string get_repo_id() const override;
    virtual std::string get_location() const override;
    virtual std::string get_url() const override;
    virtual uint64_t get_size() const override;
    virtual const IRepository & get_repository() const override;
    virtual IRepository & get_repository() override;
    virtual const IChecksum & get_checksum() const override;
    virtual IChecksum & get_checksum() override;
    virtual const INevra & get_nevra() const override;
    virtual INevra & get_nevra() override;
    virtual const INevra & get_srpm() const override;
    virtual INevra & get_srpm() override;
    virtual const IModule & get_module() const override;
    virtual IModule & get_module() override;
    virtual const std::vector<std::string> & get_parent_archs() const override;
    virtual std::vector<std::string> & get_parent_archs() override;

    virtual void set_repo_id(const std::string & repo_id) override;
    virtual void set_location(const std::string & location) override;
    virtual void set_size(uint64_t size) override;
    virtual void set_checksum(std::unique_ptr<IChecksum> checksum) override;
    virtual void set_nevra(std::unique_ptr<INevra> nevra) override;
    virtual void set_srpm(std::unique_ptr<INevra> srpm) override;
    virtual void set_module(std::unique_ptr<IModule> module) override;
    virtual void set_repository(IRepository & repository) override;

private:
    void check_repository() const;

    std::string repo_id;
    std::string location;
    uint64_t size;
    std::unique_ptr<IChecksum> checksum;
    std::unique_ptr<INevra> nevra;
    std::unique_ptr<INevra> srpm;
    std::unique_ptr<IModule> module;
    IRepository * repository;
    std::vector<std::string> parent_archs;
};

}