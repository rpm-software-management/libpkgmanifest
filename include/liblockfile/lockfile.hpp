#pragma once

#include "packages.hpp"
#include "version.hpp"

#include <memory>
#include <string>

namespace liblockfile {

class LockFile {
public:
    ~LockFile();

    LockFile(const LockFile & other);
    LockFile & operator=(const LockFile & other);

    LockFile(LockFile && other) noexcept;
    LockFile & operator=(LockFile && other) noexcept;

    std::string get_document() const;
    const Version & get_version() const;
    const Packages & get_packages() const;

private:
    friend class Parser;
    friend class Serializer;

    LockFile();

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}