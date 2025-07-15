// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/manifest/imanifestparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ManifestParserMock : public IManifestParser {
public:
    MOCK_METHOD(std::unique_ptr<IManifest>, parse, (const IYamlNode &), (const, override));
};

}
