#include "impl/common/objects/repository/irepository.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class RepositoryMock : public IRepository {
public:
    MOCK_METHOD(std::unique_ptr<IRepository>, clone, (), (const, override));
    MOCK_METHOD(std::string, get_id, (), (const, override));
    MOCK_METHOD(std::string, get_baseurl, (), (const, override));
    MOCK_METHOD(std::string, get_metalink, (), (const, override));
    MOCK_METHOD(std::string, get_mirrorlist, (), (const, override));
    MOCK_METHOD(void, set_id, (const std::string &), (override));
    MOCK_METHOD(void, set_baseurl, (const std::string &), (override));
    MOCK_METHOD(void, set_metalink, (const std::string &), (override));
    MOCK_METHOD(void, set_mirrorlist, (const std::string &), (override));
};

}
