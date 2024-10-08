#include "impl/libpkgmanifest/objects/package/ipackageparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class PackageParserMock : public IPackageParser {
public:
    MOCK_METHOD(std::unique_ptr<IPackage>, parse, (const std::string &, const IYamlNode &), (const, override));
};

}
