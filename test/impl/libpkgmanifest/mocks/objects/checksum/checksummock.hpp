#include "impl/libpkgmanifest/objects/checksum/ichecksum.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class ChecksumMock : public IChecksum {
public:
    MOCK_METHOD(std::unique_ptr<IChecksum>, clone, (), (const, override));
    MOCK_METHOD(libpkgmanifest::ChecksumMethod, get_method, (), (const, override));
    MOCK_METHOD(std::string, get_digest, (), (const, override));
    MOCK_METHOD(void, set_method, (libpkgmanifest::ChecksumMethod), (override));
    MOCK_METHOD(void, set_digest, (const std::string &), (override));
};

}
