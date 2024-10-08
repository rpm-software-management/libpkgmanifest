#include "impl/libpkgmanifest/objects/manifest/imanifestparser.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class ManifestParserMock : public IManifestParser {
public:
    MOCK_METHOD(std::unique_ptr<IManifest>, parse, (const IYamlNode &), (const, override));
};

}
