#pragma once

#include "ipackagesfactory.hpp"
#include "ipackagesparser.hpp"

#include "liblockfile/objects/package/ipackageparser.hpp"

namespace liblockfile {

class PackagesParser : IPackagesParser {
public:
    PackagesParser(const IPackageParser & package_parser, const IPackagesFactory & packages_factory);

    virtual std::unique_ptr<IPackagesInternal> parse(const IYamlNode & node) const override;

private:
    const IPackageParser & package_parser;
    const IPackagesFactory & packages_factory;
};

}