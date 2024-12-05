#include "impl/manifest/objects/checksum/ichecksumfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ChecksumFactoryMock : public IChecksumFactory {
public:
    MOCK_METHOD(std::unique_ptr<IChecksum>, create, (), (const, override));
};

}
