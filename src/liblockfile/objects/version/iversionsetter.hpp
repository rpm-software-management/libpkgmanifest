#pragma once

namespace liblockfile {

class IVersionSetter {
public:
    virtual ~IVersionSetter() = default;

    virtual void set_major(int major) = 0;
    virtual void set_minor(int minor) = 0;
    virtual void set_patch(int patch) = 0;
};

}