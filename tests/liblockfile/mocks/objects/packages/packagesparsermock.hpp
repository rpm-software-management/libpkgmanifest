#include "liblockfile/objects/packages/ipackagesparser.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class PackagesParserMock : public IPackagesParser {
public:
    MOCK_METHOD(std::unique_ptr<IPackagesInternal>, parse, (const IYamlNode &), (const, override));
};

}
