#include "checksumparser.hpp"

namespace liblockfile {

std::unique_ptr<IChecksum> ChecksumParser::parse([[maybe_unused]] IYamlNode & node) const {
    throw; // TODO
}

}