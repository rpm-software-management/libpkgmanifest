#include "libpkgmanifest/objects/package/ipackage.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal;

namespace {

class PackageMock : public IPackage {
public:
    MOCK_METHOD(std::unique_ptr<IPackage>, clone, (), (const, override));
    MOCK_METHOD(std::string, get_repo_id, (), (const, override));
    MOCK_METHOD(std::string, get_location, (), (const, override));
    MOCK_METHOD(std::string, get_url, (), (const, override));
    MOCK_METHOD(uint64_t, get_size, (), (const, override));
    MOCK_METHOD(const IRepository &, get_repository, (), (const, override));
    MOCK_METHOD(IRepository &, get_repository, (), (override));
    MOCK_METHOD(const IChecksum &, get_checksum, (), (const, override));
    MOCK_METHOD(IChecksum &, get_checksum, (), (override));
    MOCK_METHOD(const INevra &, get_nevra, (), (const, override));
    MOCK_METHOD(INevra &, get_nevra, (), (override));
    MOCK_METHOD(const INevra &, get_srpm, (), (const, override));
    MOCK_METHOD(INevra &, get_srpm, (), (override));
    MOCK_METHOD(const IModule &, get_module, (), (const, override));
    MOCK_METHOD(IModule &, get_module, (), (override));
    MOCK_METHOD(void, set_repo_id, (const std::string &), (override));
    MOCK_METHOD(void, set_location, (const std::string &), (override));
    MOCK_METHOD(void, set_size, (uint64_t), (override));
    MOCK_METHOD(void, set_checksum, (std::unique_ptr<IChecksum>), (override));
    MOCK_METHOD(void, set_nevra, (std::unique_ptr<INevra>), (override));
    MOCK_METHOD(void, set_srpm, (std::unique_ptr<INevra>), (override));
    MOCK_METHOD(void, set_module, (std::unique_ptr<IModule>), (override));
    MOCK_METHOD(void, set_repository, (IRepository &), (override));
};

}
