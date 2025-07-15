// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/module/imoduleserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ModuleSerializerMock : public IModuleSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IModule &), (const, override));
};

}
