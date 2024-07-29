#include "liblockfile/objects/lockfile/ilockfilesetter.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class LockFileSetterMock : public ILockFileSetter {
public:
    MOCK_METHOD(void, set_document, (const std::string &), (override));
    MOCK_METHOD(void, set_version, (std::unique_ptr<IVersion>), (override));
    MOCK_METHOD(void, set_packages, (std::unique_ptr<IPackages>), (override));
};

}
