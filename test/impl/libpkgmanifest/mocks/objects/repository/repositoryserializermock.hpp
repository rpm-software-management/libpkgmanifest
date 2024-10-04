#include "libpkgmanifest/objects/repository/irepositoryserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class RepositorySerializerMock : public IRepositorySerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IRepository &), (const, override));
};

}
