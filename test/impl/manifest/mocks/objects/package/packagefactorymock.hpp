// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/package/ipackagefactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class PackageFactoryMock : public IPackageFactory {
public:
    MOCK_METHOD(std::unique_ptr<IPackage>, create, (), (const, override));
};

}
