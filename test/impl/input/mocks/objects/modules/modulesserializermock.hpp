// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/objects/modules/imodulesserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class ModulesSerializerMock : public IModulesSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IModules &), (const, override));
};

}  // namespace
