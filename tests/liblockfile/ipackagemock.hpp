#include "ipackage.hpp"

#include <gmock/gmock.h>

using namespace liblockfile;

namespace {

class PackageMock : public IPackage {
public:
    MOCK_METHOD(std::string, get_arch, (), (const, override));
    MOCK_METHOD(std::string, get_repo_id, (), (const, override));
    MOCK_METHOD(std::string, get_url, (), (const, override));
    MOCK_METHOD(IChecksum &, get_checksum, (), (const, override));
    MOCK_METHOD(uint64_t, get_size, (), (const, override));
    MOCK_METHOD(std::string, get_nevra, (), (const, override));
    MOCK_METHOD(std::string, get_srpm, (), (const, override));
};

}
