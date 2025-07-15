// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/objects/repository/irepositoryfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class RepositoryFactoryMock : public IRepositoryFactory {
public:
    MOCK_METHOD(std::unique_ptr<IRepository>, create, (), (const, override));
};

}
