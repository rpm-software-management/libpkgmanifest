#include "liblockfile/objects/package/ipackageparser.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class PackageParserMock : public IPackageParser {
public:
    MOCK_METHOD(std::unique_ptr<IPackageInternal>, parse, (const std::string &, const IYamlNode &), (const, override));
};

}
