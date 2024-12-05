#pragma once

#include "irepositoryfactory.hpp"

namespace libpkgmanifest::internal::common {

class RepositoryFactory : public IRepositoryFactory {
public:
    virtual std::unique_ptr<IRepository> create() const override;
};

}