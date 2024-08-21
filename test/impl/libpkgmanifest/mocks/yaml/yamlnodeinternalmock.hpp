#include "libpkgmanifest/yaml/iyamlnodeinternal.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class YamlNodeInternalMock : public IYamlNodeInternal {
public:
    MOCK_METHOD(std::unique_ptr<IYamlNode>, get, (const std::string &), (const, override));
    MOCK_METHOD(std::string, as_string, (), (const, override));
    MOCK_METHOD(int, as_int, (), (const, override));
    MOCK_METHOD(unsigned, as_uint, (), (const, override));
    MOCK_METHOD(uint64_t, as_uint64, (), (const, override));
    MOCK_METHOD(std::vector<std::unique_ptr<IYamlNode>>, as_list, (), (const, override));
    MOCK_METHOD((std::map<std::string, std::unique_ptr<IYamlNode>>), as_map, (), (const, override));
    MOCK_METHOD(void, set, (const std::string &), (override));
    MOCK_METHOD(void, set, (int), (override));
    MOCK_METHOD(void, set, (unsigned), (override));
    MOCK_METHOD(void, set, (uint64_t), (override));
    MOCK_METHOD(void, add, (std::unique_ptr<IYamlNode>), (override));
    MOCK_METHOD(void, insert, (const std::string &, std::unique_ptr<IYamlNode>), (override));
};

}
