#include "impl/input/objects/input/iinput.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class InputMock : public IInput {
public:
    MOCK_METHOD(std::unique_ptr<IInput>, clone, (), (const, override));
    MOCK_METHOD(std::string, get_document, (), (const, override));
    MOCK_METHOD(const IVersion &, get_version, (), (const, override));
    MOCK_METHOD(IVersion &, get_version, (), (override));
    MOCK_METHOD(const IRepositories &, get_repositories, (), (const, override));
    MOCK_METHOD(IRepositories &, get_repositories, (), (override));
    MOCK_METHOD(const IPackages &, get_packages, (), (const, override));
    MOCK_METHOD(IPackages &, get_packages, (), (override));
    MOCK_METHOD(const IModules &, get_modules, (), (const, override));
    MOCK_METHOD(IModules &, get_modules, (), (override));
    MOCK_METHOD(const std::vector<std::string> &, get_archs, (), (const, override));
    MOCK_METHOD(std::vector<std::string> &, get_archs, (), (override));
    MOCK_METHOD(const IOptions &, get_options, (), (const, override));
    MOCK_METHOD(IOptions &, get_options, (), (override));
    MOCK_METHOD(void, set_document, (const std::string &), (override));
    MOCK_METHOD(void, set_version, (std::unique_ptr<IVersion>), (override));
    MOCK_METHOD(void, set_repositories, (std::unique_ptr<IRepositories>), (override));
    MOCK_METHOD(void, set_packages, (std::unique_ptr<IPackages>), (override));
    MOCK_METHOD(void, set_modules, (std::unique_ptr<IModules>), (override));
    MOCK_METHOD(void, set_options, (std::unique_ptr<IOptions>), (override));
};

}
