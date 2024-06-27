#pragma once

#include "ipackagesparser.hpp"

#include "liblockfile/objects/package/ipackageparser.hpp"

namespace liblockfile {

class PackagesParser : IPackagesParser {
public:
    PackagesParser(const IPackageParser & package_parser);

    virtual std::unique_ptr<IPackages> parse(IYamlNode & node) const override;

private:
    const IPackageParser & package_parser;
};

}