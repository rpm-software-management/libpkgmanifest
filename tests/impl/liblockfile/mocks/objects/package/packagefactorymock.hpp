#include "liblockfile/objects/package/ipackagefactory.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class PackageFactoryMock : public IPackageFactory {
public:
    MOCK_METHOD(std::unique_ptr<IPackageInternal>, create, (), (const, override));
};

}
