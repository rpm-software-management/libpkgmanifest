#include "impl/common/objects/version/iversionserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class VersionSerializerMock : public IVersionSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IVersion &), (const, override));
};

}
