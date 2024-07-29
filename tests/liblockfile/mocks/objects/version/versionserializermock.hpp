#include "liblockfile/objects/version/iversionserializer.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class VersionSerializerMock : public IVersionSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IVersion &), (const, override));
};

}
