// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "repositories.hpp"
#include "repositoriesfactory.hpp"

namespace libpkgmanifest::internal::common {

std::unique_ptr<IRepositories> RepositoriesFactory::create() const {
    return std::make_unique<Repositories>();
}   

}