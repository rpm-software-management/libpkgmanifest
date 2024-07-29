#pragma once

namespace liblockfile {

class IVersion {
public:
    virtual ~IVersion() = default;

    virtual unsigned get_major() const = 0;
    virtual unsigned get_minor() const = 0;
    virtual unsigned get_patch() const = 0;
};

}