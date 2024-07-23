#include "liblockfile/yaml/iyamlnodefactory.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class YamlNodeFactoryMock : public IYamlNodeFactory {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNodeInternal>, create, (), (const, override));
};

}
