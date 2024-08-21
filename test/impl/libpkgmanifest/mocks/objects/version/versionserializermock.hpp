#include "libpkgmanifest/objects/version/iversionserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class VersionSerializerMock : public IVersionSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IVersion &), (const, override));
};

}
