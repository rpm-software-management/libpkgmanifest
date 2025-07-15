// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/objects/modules/imodulesfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class ModulesFactoryMock : public IModulesFactory {
public:
    MOCK_METHOD(std::unique_ptr<IModules>, create, (), (const, override));
};

}
