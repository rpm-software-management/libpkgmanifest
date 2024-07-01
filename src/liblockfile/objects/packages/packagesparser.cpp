#include "packagesparser.hpp"

namespace liblockfile {

PackagesParser::PackagesParser(const IPackageParser & package_parser, const IPackagesFactory & packages_factory)
    : package_parser(package_parser)
    , packages_factory(packages_factory) {}

std::unique_ptr<IPackagesInternal> PackagesParser::parse(const IYamlNode & node) const {
    auto packages = packages_factory.create();
    for(auto const & [arch, package_nodes] : node.as_map()) {
        for(auto & package_node : package_nodes->as_list()) {
            auto package = package_parser.parse(arch, *package_node);
            packages->add(std::move(package));
        }
    }
    return packages;
}

}