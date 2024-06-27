#pragma once

#include "iversioninternal.hpp"

namespace liblockfile {

class Version : IVersionInternal {
public:
    virtual int get_major() const override;
    virtual int get_minor() const override;
    virtual int get_patch() const override;

    virtual void set_major(int major) override;
    virtual void set_minor(int minor) override;
    virtual void set_patch(int patch) override;

private:
    int major;
    int minor;
    int patch;
};

}