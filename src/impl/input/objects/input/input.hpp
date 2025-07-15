// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iinput.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class Input : public IInput {
public:
    Input();
    Input(const Input & other);

    virtual std::unique_ptr<IInput> clone() const override;

    virtual std::string get_document() const override;
    virtual const IVersion & get_version() const override;
    virtual IVersion & get_version() override;
    virtual const IRepositories & get_repositories() const override;
    virtual IRepositories & get_repositories() override;
    virtual const IPackages & get_packages() const override;
    virtual IPackages & get_packages() override;
    virtual const IModules & get_modules() const override;
    virtual IModules & get_modules() override;
    virtual const std::vector<std::string> & get_archs() const override;
    virtual std::vector<std::string> & get_archs() override;
    virtual const IOptions & get_options() const override;
    virtual IOptions & get_options() override;

    virtual void set_document(const std::string & document) override;
    virtual void set_version(std::unique_ptr<IVersion> version) override;
    virtual void set_repositories(std::unique_ptr<IRepositories> repositories) override;
    virtual void set_packages(std::unique_ptr<IPackages> packages) override;
    virtual void set_modules(std::unique_ptr<IModules> modules) override;
    virtual void set_options(std::unique_ptr<IOptions> options) override;

private:
    std::string document;
    std::unique_ptr<IVersion> version;
    std::unique_ptr<IRepositories> repositories;
    std::unique_ptr<IPackages> packages;
    std::unique_ptr<IModules> modules;
    std::unique_ptr<IOptions> options;
    std::vector<std::string> archs;
};

}