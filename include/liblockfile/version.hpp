#pragma once

#include <memory>

namespace liblockfile {

class Version {
public:
    unsigned get_major() const;
    unsigned get_minor() const;
    unsigned get_patch() const;

private:
    friend class LockFile;

    Version();
    ~Version();

    class Impl;
    std::unique_ptr<Impl> p_impl;
};

}