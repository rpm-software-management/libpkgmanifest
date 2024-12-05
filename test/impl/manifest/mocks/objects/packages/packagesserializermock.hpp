#include "impl/manifest/objects/packages/ipackagesserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class PackagesSerializerMock : public IPackagesSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IPackages &), (const, override));
};

}
