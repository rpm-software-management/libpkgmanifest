#include "impl/input/operations/prototypefileconverter/iprototypefileconverter.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class PrototypeFileConverterMock : public IPrototypeFileConverter {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, convert, (const IYamlNode &), (const, override));
};

}
