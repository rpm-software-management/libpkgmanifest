#include "impl/libpkgmanifest/operations/iprototypeinfileconverter.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class PrototypeInFileConverterMock : public IPrototypeInFileConverter {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, convert, (const IYamlNode &), (const, override));
};

}
