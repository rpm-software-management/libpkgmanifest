// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/objects/repositories/irepositories.hpp"
#include "impl/common/objects/version/iversion.hpp"
#include "impl/input/objects/modules/imodules.hpp"
#include "impl/input/objects/options/ioptions.hpp"
#include "impl/input/objects/packages/ipackages.hpp"

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class IInput {
public:
    virtual ~IInput() = default;

    virtual std::unique_ptr<IInput> clone() const = 0;

    virtual std::string get_document() const = 0;
    virtual const IVersion & get_version() const = 0;
    virtual IVersion & get_version() = 0;
    virtual const IRepositories & get_repositories() const = 0;
    virtual IRepositories & get_repositories() = 0;
    virtual const IPackages & get_packages() const = 0;
    virtual IPackages & get_packages() = 0;
    virtual const IModules & get_modules() const = 0;
    virtual IModules & get_modules() = 0;
    virtual const std::vector<std::string> & get_archs() const = 0;
    virtual std::vector<std::string> & get_archs() = 0;
    virtual const IOptions & get_options() const = 0;
    virtual IOptions & get_options() = 0;

    virtual void set_document(const std::string & document) = 0;
    virtual void set_version(std::unique_ptr<IVersion> version) = 0;
    virtual void set_repositories(std::unique_ptr<IRepositories> repositories) = 0;
    virtual void set_packages(std::unique_ptr<IPackages> packages) = 0;
    virtual void set_modules(std::unique_ptr<IModules> modules) = 0;
    virtual void set_options(std::unique_ptr<IOptions> options) = 0;
};

}