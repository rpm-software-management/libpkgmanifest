#include "impl/libpkgmanifest/objects/input/iinputparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class InputParserMock : public IInputParser {
public:
    MOCK_METHOD(std::unique_ptr<IInput>, parse, (const IYamlNode &), (const, override));
};

}
