// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/objects/options/ioptionsserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class OptionsSerializerMock : public IOptionsSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IOptions &), (const, override));
};

}  // namespace
