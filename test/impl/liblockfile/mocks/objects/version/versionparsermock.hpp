#include "liblockfile/objects/version/iversionparser.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class VersionParserMock : public IVersionParser {
public:
    MOCK_METHOD(std::unique_ptr<IVersion>, parse, (const IYamlNode &), (const, override));
};

}
