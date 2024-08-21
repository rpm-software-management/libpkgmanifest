#include "packageparser.hpp"

namespace libpkgmanifest::internal {

PackageParser::PackageParser(std::unique_ptr<IChecksumParser> checksum_parser, std::unique_ptr<IPackageFactory> package_factory)
    : checksum_parser(std::move(checksum_parser))
    , package_factory(std::move(package_factory)) {}

std::unique_ptr<IPackage> PackageParser::parse(const std::string & arch, const IYamlNode & node) const {
    auto package = package_factory->create();

    package->set_arch(arch);
    package->set_repo_id(node.get("repoid")->as_string());
    package->set_url(node.get("url")->as_string());
    package->set_checksum(checksum_parser->parse(*node.get("checksum")));
    package->set_size(node.get("size")->as_uint64());
    package->set_nevra(node.get("nevra")->as_string());
    package->set_srpm(node.get("srpm")->as_string());

    return package;
}

}