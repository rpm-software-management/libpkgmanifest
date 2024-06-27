#pragma once

#include "ipackageparser.hpp"

#include "liblockfile/objects/checksum/ichecksumparser.hpp"

namespace liblockfile {

class PackageParser : IPackageParser {
public:
    PackageParser(const IChecksumParser & checksum_parser);

    virtual std::unique_ptr<IPackage> parse(IYamlNode & node) const override;

private:
    const IChecksumParser & checksum_parser;
};

}