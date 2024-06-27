#pragma once

#include "ichecksumparser.hpp"

namespace liblockfile {

class ChecksumParser : IChecksumParser {
public:
    virtual std::unique_ptr<IChecksum> parse(IYamlNode & node) const override;
};

}