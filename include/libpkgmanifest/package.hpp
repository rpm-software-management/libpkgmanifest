#pragma once

#include "checksum.hpp"

#include <memory>
#include <stdint.h>
#include <string>

namespace libpkgmanifest {

class Package {
public:
    Package();
    ~Package();

    Package(const Package & other);
    Package & operator=(const Package & other);

    Package(Package && other) noexcept;
    Package & operator=(Package && other) noexcept;

    std::string get_arch() const;
    std::string get_repo_id() const;
    std::string get_url() const;
    Checksum & get_checksum();
    uint64_t get_size() const;
    std::string get_nevra() const;
    std::string get_srpm() const;

    void set_arch(const std::string & arch);
    void set_repo_id(const std::string & repo_id);
    void set_url(const std::string & url);
    void set_checksum(Checksum & checksum);
    void set_size(uint64_t size);
    void set_nevra(const std::string & nevra);
    void set_srpm(const std::string & srpm);

private:
    friend class Packages;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}