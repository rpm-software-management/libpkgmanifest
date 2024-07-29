#include "liblockfile/objects/packages/ipackagesinternal.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class PackagesInternalMock : public IPackagesInternal {
public:
    MOCK_METHOD((std::map<std::string, std::vector<std::unique_ptr<IPackage>>>) &, get, (), (const, override));
    MOCK_METHOD(std::vector<std::unique_ptr<IPackage>> &, get, (const std::string &), (const, override));
    MOCK_METHOD(void, add, (std::unique_ptr<IPackage>), (override));
};

}
