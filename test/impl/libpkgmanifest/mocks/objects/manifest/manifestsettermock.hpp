#include "impl/libpkgmanifest/objects/manifest/imanifestsetter.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class ManifestSetterMock : public IManifestSetter {
public:
    MOCK_METHOD(void, set_document, (const std::string &), (override));
    MOCK_METHOD(void, set_version, (std::unique_ptr<IVersion>), (override));
    MOCK_METHOD(void, set_packages, (std::unique_ptr<IPackages>), (override));
};

}
