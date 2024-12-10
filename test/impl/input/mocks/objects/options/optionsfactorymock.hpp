#include "impl/input/objects/options/ioptionsfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class OptionsFactoryMock : public IOptionsFactory {
public:
    MOCK_METHOD(std::unique_ptr<IOptions>, create, (), (const, override));
};

}
