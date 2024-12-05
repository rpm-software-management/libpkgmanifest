#include "impl/manifest/objects/manifest/imanifestserializer.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class ManifestSerializerMock : public IManifestSerializer {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, serialize, (const IManifest &), (const, override));
};

}
