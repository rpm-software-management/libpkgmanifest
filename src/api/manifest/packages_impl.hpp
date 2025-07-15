// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "libpkgmanifest/manifest/packages.hpp"

#include "api/shared/base_impl.hpp"
#include "impl/manifest/objects/packages/packagesfactory.hpp"
#include "impl/manifest/operations/packagerepositorybinder/packagerepositorybinder.hpp"

#include "package_impl.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Packages::Impl : public BaseImpl<IPackages, PackagesFactory> {
public:
    IPackageRepositoryBinder & get_binder() {
        return binder;
    }

    Package wrap_internal_item(IPackage * package) const {
        Package wrapped_package;
        wrapped_package.p_impl->init(package);
        return wrapped_package;
    }

    Package wrap_internal_item(IPackage & package) const {
        return wrap_internal_item(&package);
    }

    std::vector<Package> wrap_internal_items(auto & packages) const {
        std::vector<Package> wrapped_packages;
        wrapped_packages.reserve(std::ranges::distance(packages));

        for (const auto & package : packages) {
            wrapped_packages.push_back(wrap_internal_item(package.get()));
        }
        return wrapped_packages;
    }

private:
    PackageRepositoryBinder binder;
};

}