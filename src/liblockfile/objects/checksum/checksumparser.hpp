#pragma once

#include "ichecksumfactory.hpp"
#include "ichecksumparser.hpp"

namespace liblockfile {

class ChecksumParser : IChecksumParser {
public:
    ChecksumParser(const IChecksumFactory & checksum_factory);

    virtual std::unique_ptr<IChecksumInternal> parse(const IYamlNode & node) const override;

private:
    const IChecksumFactory & checksum_factory;
};

}