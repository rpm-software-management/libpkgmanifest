#include "liblockfile/objects/checksum/ichecksumfactory.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class ChecksumFactoryMock : public IChecksumFactory {
public:
    MOCK_METHOD(std::unique_ptr<IChecksumInternal>, create, (), (const, override));
};

}
