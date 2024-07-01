#include "packageparser.hpp"

namespace liblockfile {

PackageParser::PackageParser(const IChecksumParser & checksum_parser, const IPackageFactory & package_factory)
    : checksum_parser(checksum_parser)
    , package_factory(package_factory) {}

std::unique_ptr<IPackageInternal> PackageParser::parse(const std::string & arch, const IYamlNode & node) const {
    auto package = package_factory.create();

    package->set_arch(arch);
    package->set_repo_id(node.get("repoid")->as_string());
    package->set_checksum(checksum_parser.parse(*node.get("checksum")));
    package->set_size(node.get("size")->as_uint64());
    package->set_nevra(node.get("nevra")->as_string());
    package->set_srpm(node.get("srpm")->as_string());

    return package;
}

}