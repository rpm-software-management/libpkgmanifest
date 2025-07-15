// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/packages/ipackages.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class PackagesMock : public IPackages {
public:
    MOCK_METHOD(std::unique_ptr<IPackages>, clone, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>), get_archs, (), (const, override));
    MOCK_METHOD((const std::vector<std::unique_ptr<IPackage>> &), get, (const std::string &), (const, override));
    MOCK_METHOD(void, add, (std::unique_ptr<IPackage>), (override));
    MOCK_METHOD(void, add, (std::unique_ptr<IPackage>, const std::string & basearch), (override));
    MOCK_METHOD(bool, contains, (const IPackage &), (const, override));
};

}
