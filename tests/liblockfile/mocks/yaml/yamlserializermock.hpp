#include "liblockfile/yaml/iyamlserializer.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class YamlSerializerMock : public IYamlSerializer {
public:
    MOCK_METHOD(std::string, to_string, (const IYamlNode &), (const, override));
    MOCK_METHOD(void, to_file, (const IYamlNode &, const std::string &), (const, override));
};

}
