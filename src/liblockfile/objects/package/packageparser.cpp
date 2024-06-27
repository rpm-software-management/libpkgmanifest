#include "packageparser.hpp"

namespace liblockfile {

PackageParser::PackageParser(const IChecksumParser & checksum_parser)
    : checksum_parser(checksum_parser) {}

std::unique_ptr<IPackage> PackageParser::parse([[maybe_unused]] IYamlNode & node) const {
    throw; // TODO
}

}