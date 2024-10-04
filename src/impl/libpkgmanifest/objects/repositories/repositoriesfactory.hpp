#pragma once

#include "irepositoriesfactory.hpp"

namespace libpkgmanifest::internal {

class RepositoriesFactory : public IRepositoriesFactory {
public:
    virtual std::unique_ptr<IRepositories> create() const override;
};

}