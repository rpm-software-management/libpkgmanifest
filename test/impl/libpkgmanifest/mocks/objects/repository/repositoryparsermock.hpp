#include "impl/libpkgmanifest/objects/repository/irepositoryparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class RepositoryParserMock : public IRepositoryParser {
public:
    MOCK_METHOD(std::unique_ptr<IRepository>, parse, (const IYamlNode &), (const, override));
};

}
