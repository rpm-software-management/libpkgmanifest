#pragma once

#include "iversionfactory.hpp"
#include "iversionparser.hpp"

namespace liblockfile {

class VersionParser : IVersionParser {
public:
    VersionParser(const IVersionFactory & version_factory);

    virtual std::unique_ptr<IVersionInternal> parse(const IYamlNode & node) const override;

private:
    const IVersionFactory & version_factory;
};

}