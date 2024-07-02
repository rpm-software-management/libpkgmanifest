#include "liblockfile/yaml/iyamlparser.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class YamlParserMock : public IYamlParser {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, from_string, (const std::string &), (const, override));
    MOCK_METHOD(std::unique_ptr<IYamlNode>, from_file, (const std::string &), (const, override));
};

}
