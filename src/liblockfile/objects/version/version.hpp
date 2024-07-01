#pragma once

#include "iversioninternal.hpp"

namespace liblockfile {

class Version : public IVersionInternal {
public:
    Version();

    virtual unsigned get_major() const override;
    virtual unsigned get_minor() const override;
    virtual unsigned get_patch() const override;

    virtual void set_major(unsigned major) override;
    virtual void set_minor(unsigned minor) override;
    virtual void set_patch(unsigned patch) override;

private:
    unsigned major;
    unsigned minor;
    unsigned patch;
};

}