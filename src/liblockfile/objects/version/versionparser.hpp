#pragma once

#include "iversionparser.hpp"

namespace liblockfile {

class VersionParser : IVersionParser {
public:
    virtual std::unique_ptr<IVersion> parse(IYamlNode & node) const override;
};

}