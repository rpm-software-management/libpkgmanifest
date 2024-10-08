#include "impl/libpkgmanifest/yaml/iyamlnodefactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class YamlNodeFactoryMock : public IYamlNodeFactory {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNodeInternal>, create, (), (const, override));
};

}
