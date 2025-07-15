// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/objects/repositories/irepositoriesfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class RepositoriesFactoryMock : public IRepositoriesFactory {
public:
    MOCK_METHOD(std::unique_ptr<IRepositories>, create, (), (const, override));
};

}
