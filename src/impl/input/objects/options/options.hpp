#pragma once

#include "ioptions.hpp"

namespace libpkgmanifest::internal::input {

class Options : public IOptions {
public:
    Options();

    virtual std::unique_ptr<IOptions> clone() const override;

    virtual bool get_allow_erasing() const override;
    virtual void set_allow_erasing(bool allow_erasing) override;

private:
    bool allow_erasing;
};

}