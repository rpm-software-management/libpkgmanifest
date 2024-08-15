#include "liblockfile/objects/lockfile/ilockfile.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class LockFileMock : public ILockFile {
public:
    MOCK_METHOD(std::unique_ptr<ILockFile>, clone, (), (const, override));
    MOCK_METHOD(std::string, get_document, (), (const, override));
    MOCK_METHOD(const IVersion &, get_version, (), (const, override));
    MOCK_METHOD(IVersion &, get_version, (), (override));
    MOCK_METHOD(const IPackages &, get_packages, (), (const, override));
    MOCK_METHOD(IPackages &, get_packages, (), (override));
    MOCK_METHOD(void, set_document, (const std::string &), (override));
    MOCK_METHOD(void, set_version, (std::unique_ptr<IVersion>), (override));
    MOCK_METHOD(void, set_packages, (std::unique_ptr<IPackages>), (override));
};

}
