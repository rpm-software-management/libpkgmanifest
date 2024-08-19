#include "liblockfile/objects/checksum/ichecksumparser.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class ChecksumParserMock : public IChecksumParser {
public:
    MOCK_METHOD(std::unique_ptr<IChecksum>, parse, (const IYamlNode &), (const, override));
};

}
