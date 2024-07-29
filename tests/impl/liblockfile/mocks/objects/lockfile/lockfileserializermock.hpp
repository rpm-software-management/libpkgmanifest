#include "liblockfile/objects/lockfile/ilockfileserializer.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class LockFileSerializerMock : public ILockFileSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const ILockFile &), (const, override));
};

}
