#pragma once

#include "irepository.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoryFactory {
public:
    virtual ~IRepositoryFactory() = default;

    virtual std::unique_ptr<IRepository> create() const = 0;
};

}