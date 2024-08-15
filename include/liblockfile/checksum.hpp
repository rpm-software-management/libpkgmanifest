#pragma once

#include <memory>
#include <string>

namespace liblockfile {

enum class ChecksumMethod {
    SHA256, SHA512, MD5, CRC32, CRC64
};

class Checksum {
public:
    Checksum();
    ~Checksum();

    Checksum(const Checksum & other);
    Checksum & operator=(const Checksum & other);

    Checksum(Checksum && other) noexcept;
    Checksum & operator=(Checksum && other) noexcept;

    ChecksumMethod get_method() const;
    std::string get_digest() const;

    void set_method(ChecksumMethod method);
    void set_digest(const std::string & digest);

private:
    friend class Package;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}