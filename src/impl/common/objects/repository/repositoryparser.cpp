// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "repositoryparser.hpp"

#include <algorithm>
#include <cctype>

namespace libpkgmanifest::internal::common {

RepositorySourceNotProvidedError::RepositorySourceNotProvidedError(const std::string & message)
    : std::runtime_error(message) {}

RepositoryParser::RepositoryParser(std::shared_ptr<IRepositoryFactory> repository_factory)
    : repository_factory(std::move(repository_factory)) {}

std::unique_ptr<IRepository> RepositoryParser::parse(const IYamlNode & node) const {
    auto repository = repository_factory->create();
    repository->set_id(node.get("id")->as_string());

    if (!(node.has("baseurl") || node.has("metalink") || node.has("mirrorlist"))) {
        throw RepositorySourceNotProvidedError("Source for repository with ID \"" + repository->get_id() + "\" is not provided.");
    }

    if (node.has("baseurl")) {
        repository->set_baseurl(node.get("baseurl")->as_string());
    }

    if (node.has("metalink")) {
        repository->set_metalink(node.get("metalink")->as_string());
    }

    if (node.has("mirrorlist")) {
        repository->set_mirrorlist(node.get("mirrorlist")->as_string());
    }

    return repository;
}

}