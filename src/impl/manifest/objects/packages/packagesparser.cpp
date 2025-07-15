// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "packagesparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

PackagesParser::PackagesParser(std::unique_ptr<IPackageParser> package_parser, std::shared_ptr<IPackagesFactory> packages_factory)
    : package_parser(std::move(package_parser))
    , packages_factory(std::move(packages_factory)) {}

std::unique_ptr<IPackages> PackagesParser::parse(const IYamlNode & node) const {
    auto packages = packages_factory->create();
    for (auto & [arch, package_nodes] : node.as_map()) {
        for (auto & package_node : package_nodes->as_list()) {
            auto package = package_parser->parse(arch, *package_node);
            packages->add(std::move(package));
        }
    }
    return packages;
}

}