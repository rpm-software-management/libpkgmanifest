// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "repositoryfactory.hpp"

#include "repository.hpp"

namespace libpkgmanifest::internal::common {

std::unique_ptr<IRepository> RepositoryFactory::create() const {
    return std::make_unique<Repository>();
}

}  // namespace libpkgmanifest::internal::common
