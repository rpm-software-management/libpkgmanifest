#include "liblockfile/objects/packages/ipackagesserializer.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class PackagesSerializerMock : public IPackagesSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IPackages &), (const, override));
};

}
