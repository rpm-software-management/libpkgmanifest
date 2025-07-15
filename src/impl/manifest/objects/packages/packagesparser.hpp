// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackagesfactory.hpp"
#include "ipackagesparser.hpp"

#include "impl/manifest/objects/package/ipackageparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class PackagesParser : public IPackagesParser {
public:
    PackagesParser(std::unique_ptr<IPackageParser> package_parser, std::shared_ptr<IPackagesFactory> packages_factory);

    virtual std::unique_ptr<IPackages> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IPackageParser> package_parser;
    std::shared_ptr<IPackagesFactory> packages_factory;
};

}