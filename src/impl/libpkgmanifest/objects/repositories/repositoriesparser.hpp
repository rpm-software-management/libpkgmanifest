#pragma once

#include "irepositoriesfactory.hpp"
#include "irepositoriesparser.hpp"

#include "libpkgmanifest/objects/repository/irepositoryparser.hpp"

namespace libpkgmanifest::internal {

class RepositoriesParser : public IRepositoriesParser {
public:
    RepositoriesParser(std::unique_ptr<IRepositoryParser> repository_parser, std::shared_ptr<IRepositoriesFactory> repositories_factory);

    virtual std::unique_ptr<IRepositories> parse(const IYamlNode & node) const override;

private:
    std::unique_ptr<IRepositoryParser> repository_parser;
    std::shared_ptr<IRepositoriesFactory> repositories_factory;
};

}