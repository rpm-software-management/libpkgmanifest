#include "impl/common/objects/version/iversion.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class VersionMock : public IVersion {
public:
    MOCK_METHOD(std::unique_ptr<IVersion>, clone, (), (const, override));
    MOCK_METHOD(unsigned, get_major, (), (const, override));
    MOCK_METHOD(unsigned, get_minor, (), (const, override));
    MOCK_METHOD(unsigned, get_patch, (), (const, override));
    MOCK_METHOD(void, set_major, (unsigned), (override));
    MOCK_METHOD(void, set_minor, (unsigned), (override));
    MOCK_METHOD(void, set_patch, (unsigned), (override));
};

}
