// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/objects/input/iinputserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class InputSerializerMock : public IInputSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IInput &), (const, override));
};

}  // namespace
