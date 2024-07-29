#include "liblockfile/objects/version/iversioninternal.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class VersionInternalMock : public IVersionInternal {
public:
    MOCK_METHOD(unsigned, get_major, (), (const, override));
    MOCK_METHOD(unsigned, get_minor, (), (const, override));
    MOCK_METHOD(unsigned, get_patch, (), (const, override));
    MOCK_METHOD(void, set_major, (unsigned), (override));
    MOCK_METHOD(void, set_minor, (unsigned), (override));
    MOCK_METHOD(void, set_patch, (unsigned), (override));
};

}
