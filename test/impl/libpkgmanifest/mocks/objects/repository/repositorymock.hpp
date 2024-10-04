#include "libpkgmanifest/objects/repository/irepository.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class RepositoryMock : public IRepository {
public:
    MOCK_METHOD(std::unique_ptr<IRepository>, clone, (), (const, override));
    MOCK_METHOD(std::string, get_id, (), (const, override));
    MOCK_METHOD(std::string, get_url, (), (const, override));
    MOCK_METHOD(void, set_id, (const std::string &), (override));
    MOCK_METHOD(void, set_url, (const std::string &), (override));
};

}
