// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "irepositoryfactory.hpp"

namespace libpkgmanifest::internal::common {

class RepositoryFactory : public IRepositoryFactory {
public:
    virtual std::unique_ptr<IRepository> create() const override;
};

}