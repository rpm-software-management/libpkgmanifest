#pragma once

#include "ilockfileparser.hpp"

#include "liblockfile/objects/packages/ipackagesparser.hpp"
#include "liblockfile/objects/version/iversionparser.hpp"

namespace liblockfile {

class LockFileParser : ILockFileParser {
public:
    LockFileParser(
        const IPackagesParser & packages_parser,
        const IVersionParser & version_parser);

    virtual std::unique_ptr<ILockFile> parse(IYamlNode & node) const override;

private:
    const IPackagesParser & packages_parser;
    const IVersionParser & version_parser;
};

}