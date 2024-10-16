#include "impl/libpkgmanifest/operations/ipackagerepositorybinder.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class PackageRepositoryBinderMock : public IPackageRepositoryBinder {
public:
    MOCK_METHOD(void, validate, (const IRepositories &, const IPackage &), (const, override));
    MOCK_METHOD(void, validate, (const IRepositories &, const IPackages &), (const, override));
    MOCK_METHOD(void, bind, (const IRepositories &, IPackage &), (override));
    MOCK_METHOD(void, bind, (const IRepositories &, IPackages &), (override));
};

}
