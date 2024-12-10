#include "impl/input/objects/options/ioptions.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::input;

namespace {

class OptionsMock : public IOptions {
public:
    MOCK_METHOD(std::unique_ptr<IOptions>, clone, (), (const, override));
    MOCK_METHOD(bool, get_allow_erasing, (), (const, override));
    MOCK_METHOD(void, set_allow_erasing, (bool), (override));
};

}
