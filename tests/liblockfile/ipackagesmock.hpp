#include "ipackages.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class PackagesMock : public IPackages {
public:
    MOCK_METHOD(std::vector<std::unique_ptr<IPackage>> &, get_by_arch, (const std::string &), (const, override));
    MOCK_METHOD(std::vector<std::unique_ptr<IPackage>> &, get, (), (const, override));
};

}
