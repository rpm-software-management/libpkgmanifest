#include "libpkgmanifest/yaml/iyamlvalidator.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class YamlValidatorMock : public IYamlValidator {
public:
    MOCK_METHOD(void, validate, (const std::string &, const std::string &), (const, override));
};

}
