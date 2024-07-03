#include "liblockfile/tools/istringsplitter.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class StringSplitterMock : public IStringSplitter {
public:
    MOCK_METHOD(std::vector<std::string>, split, (const std::string &, char), (const, override));
};

}
