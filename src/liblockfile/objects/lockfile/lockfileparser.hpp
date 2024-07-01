#pragma once

#include "ilockfilefactory.hpp"
#include "ilockfileparser.hpp"

#include "liblockfile/objects/packages/ipackagesparser.hpp"
#include "liblockfile/objects/version/iversionparser.hpp"

namespace liblockfile {

class LockFileParser : ILockFileParser {
public:
    LockFileParser(
        const ILockFileFactory & file_factory,
        const IPackagesParser & packages_parser,
        const IVersionParser & version_parser);

    virtual std::unique_ptr<ILockFileInternal> parse(const IYamlNode & node) const override;

private:
    const ILockFileFactory & file_factory;
    const IPackagesParser & packages_parser;
    const IVersionParser & version_parser;
};

}