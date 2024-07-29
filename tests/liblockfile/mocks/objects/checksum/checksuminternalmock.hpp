#include "liblockfile/objects/checksum/ichecksuminternal.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class ChecksumInternalMock : public IChecksumInternal {
public:
    MOCK_METHOD(ChecksumMethod, get_method, (), (const, override));
    MOCK_METHOD(std::string, get_digest, (), (const, override));
    MOCK_METHOD(void, set_method, (ChecksumMethod), (override));
    MOCK_METHOD(void, set_digest, (const std::string &), (override));
};

}
