// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/manifest/imanifestfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ManifestFactoryMock : public IManifestFactory {
public:
    MOCK_METHOD(std::unique_ptr<IManifest>, create, (), (const, override));
};

}
