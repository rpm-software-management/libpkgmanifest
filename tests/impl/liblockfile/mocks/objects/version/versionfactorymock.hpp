#include "liblockfile/objects/version/iversionfactory.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class VersionFactoryMock : public IVersionFactory {
public:
    MOCK_METHOD(std::unique_ptr<IVersion>, create, (), (const, override));
};

}
