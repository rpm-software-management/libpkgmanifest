#include "libpkgmanifest/objects/repositories/irepositories.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class RepositoriesMock : public IRepositories {
public:
    MOCK_METHOD(std::unique_ptr<IRepositories>, clone, (), (const, override));
    MOCK_METHOD((const std::map<std::string, std::unique_ptr<IRepository>>) &, get, (), (const, override));
    MOCK_METHOD((std::map<std::string, std::unique_ptr<IRepository>>) &, get, (), (override));
    MOCK_METHOD(void, add, (std::unique_ptr<IRepository>), (override));
};

}
