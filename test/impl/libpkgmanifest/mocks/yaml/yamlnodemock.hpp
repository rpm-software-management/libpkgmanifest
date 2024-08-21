#include "libpkgmanifest/yaml/iyamlnode.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class YamlNodeMock : public IYamlNode {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, get, (const std::string &), (const, override));
    MOCK_METHOD(std::string, as_string, (), (const, override));
    MOCK_METHOD(int, as_int, (), (const, override));
    MOCK_METHOD(unsigned, as_uint, (), (const, override));
    MOCK_METHOD(uint64_t, as_uint64, (), (const, override));
    MOCK_METHOD(std::vector<std::unique_ptr<IYamlNode>>, as_list, (), (const, override));
    MOCK_METHOD((std::map<std::string, std::unique_ptr<IYamlNode>>), as_map, (), (const, override));
};

}
