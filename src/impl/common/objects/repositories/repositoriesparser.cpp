// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "repositoriesparser.hpp"

namespace libpkgmanifest::internal::common {

RepositoriesParser::RepositoriesParser(
    std::unique_ptr<IRepositoryParser> repository_parser, 
    std::shared_ptr<IRepositoriesFactory> repositories_factory)
    : repository_parser(std::move(repository_parser))
    , repositories_factory(std::move(repositories_factory)) {}

std::unique_ptr<IRepositories> RepositoriesParser::parse(const IYamlNode & node) const {
    auto repositories = repositories_factory->create();
    for (auto & repository_node : node.as_list()) {
        repositories->add(repository_parser->parse(*repository_node));
    }
    return repositories;
}

}