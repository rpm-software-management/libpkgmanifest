#pragma once

#include <memory>

namespace liblockfile {

class Version {
public:
    Version();
    ~Version();

    Version(const Version & other);
    Version & operator=(const Version & other);

    Version(Version && other) noexcept;
    Version & operator=(Version && other) noexcept;

    unsigned get_major() const;
    unsigned get_minor() const;
    unsigned get_patch() const;

    void set_major(unsigned major);
    void set_minor(unsigned minor);
    void set_patch(unsigned patch);

private:
    friend class LockFile;

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}