#include "impl/manifest/objects/nevra/inevrafactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::manifest;

namespace {

class NevraFactoryMock : public INevraFactory {
public:
    MOCK_METHOD(std::unique_ptr<INevra>, create, (), (const, override));
};

}