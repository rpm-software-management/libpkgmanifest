#include "versionparser.hpp"

namespace liblockfile {

std::unique_ptr<IVersion> VersionParser::parse([[maybe_unused]] IYamlNode & node) const {
    throw; // TODO
}

}