#include "libpkgmanifest/objects/repositories/irepositoriesserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class RepositoriesSerializerMock : public IRepositoriesSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IRepositories &), (const, override));
};

}
