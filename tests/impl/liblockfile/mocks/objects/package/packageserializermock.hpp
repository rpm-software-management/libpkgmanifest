#include "liblockfile/objects/package/ipackageserializer.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class PackageSerializerMock : public IPackageSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IPackage &), (const, override));
};

}
