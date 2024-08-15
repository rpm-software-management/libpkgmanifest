#include "liblockfile/objects/lockfile/ilockfilefactory.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class LockFileFactoryMock : public ILockFileFactory {
public:
    MOCK_METHOD(std::unique_ptr<ILockFile>, create, (), (const, override));
};

}
