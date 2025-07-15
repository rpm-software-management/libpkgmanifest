// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/checksum/ichecksumserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ChecksumSerializerMock : public IChecksumSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IChecksum &), (const, override));
};

}
