#include "liblockfile/objects/packages/ipackagesfactory.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class PackagesFactoryMock : public IPackagesFactory {
public:
    MOCK_METHOD(std::unique_ptr<IPackagesInternal>, create, (), (const, override));
};

}
