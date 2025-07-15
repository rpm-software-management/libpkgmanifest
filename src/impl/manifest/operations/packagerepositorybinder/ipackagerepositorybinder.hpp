// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "impl/common/objects/repositories/irepositories.hpp"
#include "impl/manifest/objects/package/ipackage.hpp"
#include "impl/manifest/objects/packages/ipackages.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class IPackageRepositoryBinder {
public:
    virtual ~IPackageRepositoryBinder() = default;

    virtual void validate(const IRepositories & repositories, const IPackage & package) const = 0;
    virtual void validate(const IRepositories & repositories, const IPackages & packages) const = 0;
    virtual void bind(const IRepositories & repositories, IPackage & package) = 0;
    virtual void bind(const IRepositories & repositories, IPackages & packages) = 0;
};

}