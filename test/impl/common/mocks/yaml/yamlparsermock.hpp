// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/yaml/iyamlparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class YamlParserMock : public IYamlParser {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, from_string, (const std::string &), (const, override));
    MOCK_METHOD(std::unique_ptr<IYamlNode>, from_file, (const std::string &), (const, override));
};

}
