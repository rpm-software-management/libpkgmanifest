#pragma once

#include "ipackagefactory.hpp"
#include "ipackageparser.hpp"

#include "liblockfile/objects/checksum/ichecksumparser.hpp"

namespace liblockfile::internal {

class PackageParser : public IPackageParser {
public:
    PackageParser(std::unique_ptr<IChecksumParser> checksum_parser, std::unique_ptr<IPackageFactory> package_factory);

    virtual std::unique_ptr<IPackageInternal> parse(const std::string & arch, const IYamlNode & node) const override;

private:
    std::unique_ptr<IChecksumParser> checksum_parser;
    std::unique_ptr<IPackageFactory> package_factory;
};

}