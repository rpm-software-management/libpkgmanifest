#pragma once

#include "checksum.hpp"

#include <memory>
#include <stdint.h>
#include <string>

namespace liblockfile {

class Package {
public:
    ~Package();

    Package(const Package & other);
    Package & operator=(const Package & other);

    Package(Package && other) noexcept;
    Package & operator=(Package && other) noexcept;

    std::string get_arch() const;
    std::string get_repo_id() const;
    std::string get_url() const;
    const Checksum & get_checksum() const;
    uint64_t get_size() const;
    std::string get_nevra() const;
    std::string get_srpm() const;

private:
    friend class Packages;

    Package();

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}