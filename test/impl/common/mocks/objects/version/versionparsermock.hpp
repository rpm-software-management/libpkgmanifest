#include "impl/common/objects/version/iversionparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class VersionParserMock : public IVersionParser {
public:
    MOCK_METHOD(std::unique_ptr<IVersion>, parse, (const IYamlNode &), (const, override));
};

}
