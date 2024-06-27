#include "lockfileparser.hpp"

namespace liblockfile {

LockFileParser::LockFileParser(
    const IPackagesParser & packages_parser, 
    const IVersionParser & version_parser)
    : packages_parser(packages_parser)
    , version_parser(version_parser) {}

std::unique_ptr<ILockFile> LockFileParser::parse([[maybe_unused]] IYamlNode & node) const {
    throw; // TODO
}

}