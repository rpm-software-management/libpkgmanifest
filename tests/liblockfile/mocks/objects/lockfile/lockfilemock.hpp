#include "liblockfile/objects/lockfile/ilockfile.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class LockFileMock : public ILockFile {
public:
    MOCK_METHOD(std::string, get_document, (), (const, override));
    MOCK_METHOD(const IVersion &, get_version, (), (const, override));
    MOCK_METHOD(const IPackages &, get_packages, (), (const, override));
};

}
