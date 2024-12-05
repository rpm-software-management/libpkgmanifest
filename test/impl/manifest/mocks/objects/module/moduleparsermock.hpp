#include "impl/manifest/objects/module/imoduleparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ModuleParserMock : public IModuleParser {
public:
    MOCK_METHOD(std::unique_ptr<IModule>, parse, (const IYamlNode &), (const, override));
};

}
