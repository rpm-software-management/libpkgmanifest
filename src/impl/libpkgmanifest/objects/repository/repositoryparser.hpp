#pragma once

#include "irepositoryfactory.hpp"
#include "irepositoryparser.hpp"

namespace libpkgmanifest::internal {

class RepositoryParser : public IRepositoryParser {
public:
    RepositoryParser(std::shared_ptr<IRepositoryFactory> repository_factory);

    virtual std::unique_ptr<IRepository> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IRepositoryFactory> repository_factory;
};

}