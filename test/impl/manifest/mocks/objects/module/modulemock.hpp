// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/module/imodule.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ModuleMock : public IModule {
public:
    MOCK_METHOD(std::unique_ptr<IModule>, clone, (), (const, override));
    MOCK_METHOD(std::string, get_name, (), (const, override));
    MOCK_METHOD(std::string, get_stream, (), (const, override));
    MOCK_METHOD(void, set_name, (const std::string &), (override));
    MOCK_METHOD(void, set_stream, (const std::string &), (override));
};

}
