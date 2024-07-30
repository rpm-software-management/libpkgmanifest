#pragma once

#include <memory>

namespace liblockfile {

class Version {
public:
    ~Version();

    Version(const Version & other);
    Version & operator=(const Version & other);

    Version(Version && other) noexcept;
    Version & operator=(Version && other) noexcept;

    unsigned get_major() const;
    unsigned get_minor() const;
    unsigned get_patch() const;

private:
    friend class LockFile;

    Version();

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}