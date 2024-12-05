#pragma once

#include "irepositories.hpp"

#include <memory>

namespace libpkgmanifest::internal::common {

class IRepositoriesFactory {
public:
    virtual ~IRepositoriesFactory() = default;

    virtual std::unique_ptr<IRepositories> create() const = 0;
};

}