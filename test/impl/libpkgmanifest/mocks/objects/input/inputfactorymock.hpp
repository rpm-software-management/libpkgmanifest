#include "impl/libpkgmanifest/objects/input/iinputfactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class InputFactoryMock : public IInputFactory {
public:
    MOCK_METHOD(std::unique_ptr<IInput>, create, (), (const, override));
};

}
