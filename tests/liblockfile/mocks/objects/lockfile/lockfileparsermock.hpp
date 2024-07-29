#include "liblockfile/objects/lockfile/ilockfileparser.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class LockFileParserMock : public ILockFileParser {
public:
    MOCK_METHOD(std::unique_ptr<ILockFileInternal>, parse, (const IYamlNode &), (const, override));
};

}
