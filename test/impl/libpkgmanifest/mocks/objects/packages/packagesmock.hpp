#include "libpkgmanifest/objects/packages/ipackages.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class PackagesMock : public IPackages {
public:
    MOCK_METHOD(std::unique_ptr<IPackages>, clone, (), (const, override));
    MOCK_METHOD((const std::map<std::string, std::vector<std::unique_ptr<IPackage>>>) &, get, (), (const, override));
    MOCK_METHOD((std::map<std::string, std::vector<std::unique_ptr<IPackage>>>) &, get, (), (override));
    MOCK_METHOD(void, add, (std::unique_ptr<IPackage>), (override));
};

}
