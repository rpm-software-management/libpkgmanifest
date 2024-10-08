#include "impl/libpkgmanifest/objects/module/imoduleparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class ModuleParserMock : public IModuleParser {
public:
    MOCK_METHOD(std::unique_ptr<IModule>, parse, (const IYamlNode &), (const, override));
};

}
