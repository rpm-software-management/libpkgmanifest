#include "manifestparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

ManifestParser::ManifestParser(
    std::unique_ptr<IManifestFactory> manifest_factory,
    std::unique_ptr<IPackagesParser> packages_parser,
    std::shared_ptr<IRepositoriesParser> repositories_parser,
    std::shared_ptr<IVersionParser> version_parser,
    std::shared_ptr<IPackageRepositoryBinder> binder)
    : manifest_factory(std::move(manifest_factory))
    , packages_parser(std::move(packages_parser))
    , repositories_parser(std::move(repositories_parser))
    , version_parser(std::move(version_parser))
    , binder(std::move(binder)) {}

std::unique_ptr<IManifest> ManifestParser::parse(const IYamlNode & node) const {
    auto manifest = manifest_factory->create();

    manifest->set_document(node.get("document")->as_string());
    manifest->set_version(version_parser->parse(*node.get("version")));

    auto data_node = node.get("data");
    auto repositories = repositories_parser->parse(*data_node->get("repositories"));
    auto packages = packages_parser->parse(*data_node->get("packages"));
    binder->bind(*repositories, *packages);

    manifest->set_repositories(std::move(repositories));
    manifest->set_packages(std::move(packages));

    return manifest;
}

}