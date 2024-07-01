#include "liblockfile/iversion.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class VersionMock : public IVersion {
public:
    MOCK_METHOD(unsigned, get_major, (), (const, override));
    MOCK_METHOD(unsigned, get_minor, (), (const, override));
    MOCK_METHOD(unsigned, get_patch, (), (const, override));
};

}
