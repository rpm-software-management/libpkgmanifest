#pragma once

#include "ipackagefactory.hpp"
#include "ipackageparser.hpp"

#include "liblockfile/objects/checksum/ichecksumparser.hpp"

namespace liblockfile {

class PackageParser : IPackageParser {
public:
    PackageParser(const IChecksumParser & checksum_parser, const IPackageFactory & package_factory);

    virtual std::unique_ptr<IPackageInternal> parse(const std::string & arch, const IYamlNode & node) const override;

private:
    const IChecksumParser & checksum_parser;
    const IPackageFactory & package_factory;
};

}