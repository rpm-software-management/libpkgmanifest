#include "impl/libpkgmanifest/objects/repositories/irepositoriesparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class RepositoriesParserMock : public IRepositoriesParser {
public:
    MOCK_METHOD(std::unique_ptr<IRepositories>, parse, (const IYamlNode &), (const, override));
};

}
