#include "liblockfile/objects/version/iversionfactory.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class VersionFactoryMock : public IVersionFactory {
public:
    MOCK_METHOD(std::unique_ptr<IVersionInternal>, create, (), (const, override));
};

}
