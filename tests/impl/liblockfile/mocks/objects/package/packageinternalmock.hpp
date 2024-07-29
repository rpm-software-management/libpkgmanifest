#include "liblockfile/objects/package/ipackageinternal.hpp"

#include <gmock/gmock.h>

using namespace liblockfile::internal;

namespace {

class PackageInternalMock : public IPackageInternal {
public:
    MOCK_METHOD(std::string, get_arch, (), (const, override));
    MOCK_METHOD(std::string, get_repo_id, (), (const, override));
    MOCK_METHOD(std::string, get_url, (), (const, override));
    MOCK_METHOD(IChecksum &, get_checksum, (), (const, override));
    MOCK_METHOD(uint64_t, get_size, (), (const, override));
    MOCK_METHOD(std::string, get_nevra, (), (const, override));
    MOCK_METHOD(std::string, get_srpm, (), (const, override));
    MOCK_METHOD(void, set_arch, (const std::string &), (override));
    MOCK_METHOD(void, set_repo_id, (const std::string &), (override));
    MOCK_METHOD(void, set_url, (const std::string &), (override));
    MOCK_METHOD(void, set_checksum, (std::unique_ptr<IChecksum>), (override));
    MOCK_METHOD(void, set_size, (uint64_t), (override));
    MOCK_METHOD(void, set_nevra, (const std::string &), (override));
    MOCK_METHOD(void, set_srpm, (const std::string &), (override));
};

}
