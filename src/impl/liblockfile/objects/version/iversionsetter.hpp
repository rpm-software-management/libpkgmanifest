#pragma once

namespace liblockfile::internal {

class IVersionSetter {
public:
    virtual ~IVersionSetter() = default;

    virtual void set_major(unsigned major) = 0;
    virtual void set_minor(unsigned minor) = 0;
    virtual void set_patch(unsigned patch) = 0;
};

}