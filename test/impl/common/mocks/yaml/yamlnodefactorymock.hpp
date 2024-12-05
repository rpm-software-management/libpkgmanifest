#include "impl/common/yaml/iyamlnodefactory.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class YamlNodeFactoryMock : public IYamlNodeFactory {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNodeInternal>, create, (), (const, override));
};

}
