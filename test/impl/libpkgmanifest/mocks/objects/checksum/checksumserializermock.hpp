#include "libpkgmanifest/objects/checksum/ichecksumserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class ChecksumSerializerMock : public IChecksumSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IChecksum &), (const, override));
};

}
