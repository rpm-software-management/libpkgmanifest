#pragma once

#include "ipackagesfactory.hpp"
#include "ipackagesparser.hpp"

#include "libpkgmanifest/objects/package/ipackageparser.hpp"

namespace libpkgmanifest::internal {

class PackagesParser : public IPackagesParser {
public:
    PackagesParser(std::unique_ptr<IPackageParser> package_parser, std::unique_ptr<IPackagesFactory> packages_factory);

    virtual std::unique_ptr<IPackages> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IPackageParser> package_parser;
    std::unique_ptr<IPackagesFactory> packages_factory;
};

}