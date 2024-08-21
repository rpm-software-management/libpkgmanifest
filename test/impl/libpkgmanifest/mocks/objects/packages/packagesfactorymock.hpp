#include "libpkgmanifest/objects/packages/ipackagesfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class PackagesFactoryMock : public IPackagesFactory {
public:
    MOCK_METHOD(std::unique_ptr<IPackages>, create, (), (const, override));
};

}
