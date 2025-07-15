// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/objects/input/iinputparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class InputParserMock : public IInputParser {
public:
    MOCK_METHOD(std::unique_ptr<IInput>, parse, (const IYamlNode &), (const, override));
};

}
