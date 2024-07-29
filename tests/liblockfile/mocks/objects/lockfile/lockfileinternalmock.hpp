#include "liblockfile/objects/lockfile/ilockfileinternal.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class LockFileInternalMock : public ILockFileInternal {
public:
    MOCK_METHOD(std::string, get_document, (), (const, override));
    MOCK_METHOD(const IVersion &, get_version, (), (const, override));
    MOCK_METHOD(const IPackages &, get_packages, (), (const, override));
    MOCK_METHOD(void, set_document, (const std::string &), (override));
    MOCK_METHOD(void, set_version, (std::unique_ptr<IVersion>), (override));
    MOCK_METHOD(void, set_packages, (std::unique_ptr<IPackages>), (override));
};

}
