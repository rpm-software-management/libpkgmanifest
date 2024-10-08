#include "impl/libpkgmanifest/objects/nevra/inevraparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class NevraParserMock : public INevraParser {
public:
    MOCK_METHOD(std::unique_ptr<INevra>, parse, (const IYamlNode &), (const, override));
    MOCK_METHOD(std::unique_ptr<INevra>, parse, (const std::string &, const std::string &, const IYamlNode &), (const, override));
};

}
