// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "manifestparser.hpp"

#include "manifestfactory.hpp"

#include <format>
#include <stdexcept>

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

ManifestParser::ManifestParser(
    std::unique_ptr<IManifestFactory> manifest_factory,
    std::unique_ptr<IPackagesParser> packages_parser,
    std::shared_ptr<IRepositoriesParser> repositories_parser,
    std::shared_ptr<IPackageRepositoryBinder> binder)
    : manifest_factory(std::move(manifest_factory)),
      packages_parser(std::move(packages_parser)),
      repositories_parser(std::move(repositories_parser)),
      binder(std::move(binder)) {}

std::unique_ptr<IManifest> ManifestParser::parse(const IYamlNode & node) const {
    auto document = node.get("document")->as_string();
    if (document != MANIFEST_DOCUMENT_ID) {
        throw std::runtime_error(
            std::format("Invalid document identifier: expected '{}', got '{}'", MANIFEST_DOCUMENT_ID, document));
    }

    auto version = node.get("version")->as_string();
    if (version != manifest_document_version_string()) {
        throw std::runtime_error(std::format(
            "Unsupported document version: expected '{}', got '{}'", manifest_document_version_string(), version));
    }

    auto manifest = manifest_factory->create();

    auto data_node = node.get("data");
    auto repositories = repositories_parser->parse(*data_node->get("repositories"));
    auto packages = packages_parser->parse(*data_node->get("packages"));
    binder->bind(*repositories, *packages);

    manifest->set_repositories(std::move(repositories));
    manifest->set_packages(std::move(packages));

    return manifest;
}

}  // namespace libpkgmanifest::internal::manifest
