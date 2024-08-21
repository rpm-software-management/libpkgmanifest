#include "manifestparser.hpp"

namespace libpkgmanifest::internal {

ManifestParser::ManifestParser(
    std::unique_ptr<IManifestFactory> manifest_factory,
    std::unique_ptr<IPackagesParser> packages_parser, 
    std::unique_ptr<IVersionParser> version_parser)
    : manifest_factory(std::move(manifest_factory))
    , packages_parser(std::move(packages_parser))
    , version_parser(std::move(version_parser)) {}

std::unique_ptr<IManifest> ManifestParser::parse(const IYamlNode & node) const {
    auto manifest = manifest_factory->create();

    manifest->set_document(node.get("document")->as_string());
    manifest->set_version(version_parser->parse(*node.get("version")));
    manifest->set_packages(packages_parser->parse(*node.get("data")->get("packages")));

    return manifest;
}

}