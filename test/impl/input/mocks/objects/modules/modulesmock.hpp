#include "impl/input/objects/modules/imodules.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class ModulesMock : public IModules {
public:
    MOCK_METHOD(std::unique_ptr<IModules>, clone, (), (const, override));
    MOCK_METHOD(const std::vector<std::string> &, get_enables, (), (const, override));
    MOCK_METHOD(std::vector<std::string> &, get_enables, (), (override));
    MOCK_METHOD(const std::vector<std::string> &, get_disables, (), (const, override));
    MOCK_METHOD(std::vector<std::string> &, get_disables, (), (override));
};

}
