// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "api/shared/base_impl.hpp"
#include "impl/common/objects/repository/repositoryfactory.hpp"
#include "libpkgmanifest/common/repository.hpp"

namespace libpkgmanifest::common {

using namespace libpkgmanifest::internal::common;

class Repository::Impl : public BaseImpl<IRepository, RepositoryFactory> {};

}  // namespace libpkgmanifest::common
