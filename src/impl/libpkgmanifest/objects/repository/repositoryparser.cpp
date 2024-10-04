#include "repositoryparser.hpp"

#include <algorithm>
#include <cctype>

namespace libpkgmanifest::internal {

RepositoryParser::RepositoryParser(std::shared_ptr<IRepositoryFactory> repository_factory)
    : repository_factory(repository_factory) {}

std::unique_ptr<IRepository> RepositoryParser::parse(const IYamlNode & node) const {
    auto repository = repository_factory->create();
    repository->set_id(node.get("id")->as_string());
    repository->set_url(node.get("url")->as_string());
    return repository;
}

}