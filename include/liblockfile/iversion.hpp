#pragma once

namespace liblockfile {

class IVersion {
public:
    virtual ~IVersion() = default;

    virtual int get_major() const = 0;
    virtual int get_minor() const = 0;
    virtual int get_patch() const = 0;
};

}