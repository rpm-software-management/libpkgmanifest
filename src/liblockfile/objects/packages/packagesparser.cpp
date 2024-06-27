#include "packagesparser.hpp"

namespace liblockfile {

PackagesParser::PackagesParser(const IPackageParser & package_parser)
    : package_parser(package_parser) {}

std::unique_ptr<IPackages> PackagesParser::parse([[maybe_unused]] IYamlNode & node) const {
    throw; // TODO
}

}