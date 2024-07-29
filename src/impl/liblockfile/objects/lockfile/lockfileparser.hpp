#pragma once

#include "ilockfilefactory.hpp"
#include "ilockfileparser.hpp"

#include "liblockfile/objects/packages/ipackagesparser.hpp"
#include "liblockfile/objects/version/iversionparser.hpp"

namespace liblockfile::internal {

class LockFileParser : public ILockFileParser {
public:
    LockFileParser(
        std::unique_ptr<ILockFileFactory> file_factory,
        std::unique_ptr<IPackagesParser> packages_parser,
        std::unique_ptr<IVersionParser> version_parser);

    virtual std::unique_ptr<ILockFileInternal> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<ILockFileFactory> file_factory;
    std::unique_ptr<IPackagesParser> packages_parser;
    std::unique_ptr<IVersionParser> version_parser;
};

}