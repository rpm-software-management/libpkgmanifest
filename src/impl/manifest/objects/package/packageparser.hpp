// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackagefactory.hpp"
#include "ipackageparser.hpp"

#include "impl/manifest/objects/checksum/ichecksumparser.hpp"
#include "impl/manifest/objects/nevra/inevraparser.hpp"
#include "impl/manifest/objects/module/imoduleparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class PackageSizeFormatError : public std::runtime_error {
public:
    PackageSizeFormatError(const std::string & message);
};

class PackageParser : public IPackageParser {
public:
    PackageParser(
        std::unique_ptr<IChecksumParser> checksum_parser,
        std::unique_ptr<INevraParser> nevra_parser,
        std::unique_ptr<IModuleParser> module_parser,
        std::shared_ptr<IPackageFactory> package_factory);

    virtual std::unique_ptr<IPackage> parse(const std::string & arch, const IYamlNode & node) const override;

private:
    std::unique_ptr<IChecksumParser> checksum_parser;
    std::unique_ptr<INevraParser> nevra_parser;
    std::unique_ptr<IModuleParser> module_parser;
    std::shared_ptr<IPackageFactory> package_factory;
};

}