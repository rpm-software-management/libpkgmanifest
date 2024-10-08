#include "impl/libpkgmanifest/objects/manifest/imanifestfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class ManifestFactoryMock : public IManifestFactory {
public:
    MOCK_METHOD(std::unique_ptr<IManifest>, create, (), (const, override));
};

}
