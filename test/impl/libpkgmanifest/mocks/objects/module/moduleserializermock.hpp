#include "impl/libpkgmanifest/objects/module/imoduleserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class ModuleSerializerMock : public IModuleSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IModule &), (const, override));
};

}
