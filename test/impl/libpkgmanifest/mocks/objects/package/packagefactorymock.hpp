#include "impl/libpkgmanifest/objects/package/ipackagefactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class PackageFactoryMock : public IPackageFactory {
public:
    MOCK_METHOD(std::unique_ptr<IPackage>, create, (), (const, override));
};

}
