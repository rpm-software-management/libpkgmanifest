#include "impl/input/objects/packages/ipackages.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class PackagesMock : public IPackages {
public:
    MOCK_METHOD(std::unique_ptr<IPackages>, clone, (), (const, override));
    MOCK_METHOD(const std::vector<std::string> &, get_installs, (), (const, override));
    MOCK_METHOD(std::vector<std::string> &, get_installs, (), (override));
    MOCK_METHOD(const std::vector<std::string> &, get_reinstalls, (), (const, override));
    MOCK_METHOD(std::vector<std::string> &, get_reinstalls, (), (override));
};

}
