#pragma once

#include "packages.hpp"
#include "version.hpp"

#include <memory>
#include <string>

namespace liblockfile {

class LockFile {
public:
    LockFile();
    ~LockFile();

    LockFile(const LockFile & other);
    LockFile & operator=(const LockFile & other);

    LockFile(LockFile && other) noexcept;
    LockFile & operator=(LockFile && other) noexcept;

    std::string get_document() const;
    Version & get_version();
    Packages & get_packages();

    void set_document(const std::string & document);
    void set_version(Version & version);
    void set_packages(Packages & packages);

private:
    friend class Parser;
    friend class Serializer;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}