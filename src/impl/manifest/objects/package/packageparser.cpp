#include "packageparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

PackageParser::PackageParser(
    std::unique_ptr<IChecksumParser> checksum_parser,
    std::unique_ptr<INevraParser> nevra_parser,
    std::unique_ptr<IModuleParser> module_parser,
    std::shared_ptr<IPackageFactory> package_factory)
    : checksum_parser(std::move(checksum_parser))
    , nevra_parser(std::move(nevra_parser))
    , module_parser(std::move(module_parser))
    , package_factory(package_factory) {}

std::unique_ptr<IPackage> PackageParser::parse(const std::string & arch, const IYamlNode & node) const {
    auto package = package_factory->create();

    // TODO: Handle cases when expected values are not provided
    package->set_repo_id(node.get("repo_id")->as_string());
    package->set_size(node.get("size")->as_uint64());
    package->set_nevra(nevra_parser->parse(node.get("name")->as_string(), arch, *node.get("evr")));
    package->set_checksum(checksum_parser->parse(*node.get("checksum")));

    if (node.has("location")) {
        package->set_location(node.get("location")->as_string());
    }

    if (node.has("srpm")) {
        package->set_srpm(nevra_parser->parse(*node.get("srpm")));
    }

    if (node.has("module")) {
        package->set_module(module_parser->parse(*node.get("module")));
    }

    return package;
}

}