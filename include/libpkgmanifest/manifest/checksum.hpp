#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest::manifest {

enum class ChecksumMethod {
    SHA1, SHA224, SHA256, SHA384, SHA512, MD5, CRC32, CRC64
};

/// @brief Stores information about the package checksum.
class Checksum {
public:
    Checksum();
    ~Checksum();

    Checksum(const Checksum & other);
    Checksum & operator=(const Checksum & other);

    Checksum(Checksum && other) noexcept;
    Checksum & operator=(Checksum && other) noexcept;

    /// @brief Retrieves the method used for calculating the checksum.
    ///
    /// @return The checksum calculation method.
    ChecksumMethod get_method() const;

    /// @brief Retrieves the output of the checksum hash function. 
    ///
    /// @return The checksum digest.
    std::string get_digest() const;

    /// @brief Sets the method used for calculating the checksum.
    ///
    /// @param method The checksum calculation method to be used.
    void set_method(ChecksumMethod method);

    /// @brief Sets the output of the checksum hash function.
    ///
    /// @param digest The checksum digest to be set.
    void set_digest(const std::string & digest);

private:
    friend class Package;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}