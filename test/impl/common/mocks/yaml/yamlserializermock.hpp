// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/yaml/iyamlserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class YamlSerializerMock : public IYamlSerializer {
public:
    MOCK_METHOD(std::string, to_string, (const IYamlNode &), (const, override));
    MOCK_METHOD(void, to_file, (const IYamlNode &, const std::string &), (const, override));
};

}
