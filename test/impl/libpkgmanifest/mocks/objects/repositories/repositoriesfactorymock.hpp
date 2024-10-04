#include "libpkgmanifest/objects/repositories/irepositoriesfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class RepositoriesFactoryMock : public IRepositoriesFactory {
public:
    MOCK_METHOD(std::unique_ptr<IRepositories>, create, (), (const, override));
};

}
