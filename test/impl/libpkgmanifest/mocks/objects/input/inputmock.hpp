#include "impl/libpkgmanifest/objects/input/iinput.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class InputMock : public IInput {
public:
    MOCK_METHOD(std::unique_ptr<IInput>, clone, (), (const, override));
    MOCK_METHOD(std::string, get_document, (), (const, override));
    MOCK_METHOD(const IVersion &, get_version, (), (const, override));
    MOCK_METHOD(IVersion &, get_version, (), (override));
    MOCK_METHOD(const IRepositories &, get_repositories, (), (const, override));
    MOCK_METHOD(IRepositories &, get_repositories, (), (override));
    MOCK_METHOD((const std::map<std::string, std::vector<std::string>>) &, get_packages, (), (const, override));
    MOCK_METHOD((std::map<std::string, std::vector<std::string>>) &, get_packages, (), (override));
    MOCK_METHOD((const std::map<std::string, std::vector<std::string>>) &, get_modules, (), (const, override));
    MOCK_METHOD((std::map<std::string, std::vector<std::string>>) &, get_modules, (), (override));
    MOCK_METHOD(const std::vector<std::string> &, get_archs, (), (const, override));
    MOCK_METHOD(std::vector<std::string> &, get_archs, (), (override));
    MOCK_METHOD(void, set_document, (const std::string &), (override));
    MOCK_METHOD(void, set_version, (std::unique_ptr<IVersion>), (override));
    MOCK_METHOD(void, set_repositories, (std::unique_ptr<IRepositories>), (override));
};

}
