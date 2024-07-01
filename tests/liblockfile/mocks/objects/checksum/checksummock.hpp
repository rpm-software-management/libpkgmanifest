#include "liblockfile/ichecksum.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class ChecksumMock : public IChecksum {
public:
    MOCK_METHOD(ChecksumMethod, get_method, (), (const, override));
    MOCK_METHOD(std::string, get_digest, (), (const, override));
};

}
