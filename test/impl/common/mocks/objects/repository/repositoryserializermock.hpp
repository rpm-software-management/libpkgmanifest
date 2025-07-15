// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/objects/repository/irepositoryserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class RepositorySerializerMock : public IRepositorySerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IRepository &), (const, override));
};

}
