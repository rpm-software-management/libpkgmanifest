#include "impl/libpkgmanifest/objects/nevra/inevrafactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class NevraFactoryMock : public INevraFactory {
public:
    MOCK_METHOD(std::unique_ptr<INevra>, create, (), (const, override));
};

}
