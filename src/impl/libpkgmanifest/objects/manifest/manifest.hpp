#pragma once

#include "imanifest.hpp"

namespace libpkgmanifest::internal {

class Manifest : public IManifest {
public:
    Manifest();
    Manifest(const Manifest & other);

    virtual std::unique_ptr<IManifest> clone() const override;

    virtual std::string get_document() const override;
    virtual IVersion & get_version() override;
    virtual const IVersion & get_version() const override;
    virtual IPackages & get_packages() override;
    virtual const IPackages & get_packages() const override;

    virtual void set_document(const std::string & document) override;
    virtual void set_version(std::unique_ptr<IVersion> version) override;
    virtual void set_packages(std::unique_ptr<IPackages> packages) override;

private:
    std::string document;
    std::unique_ptr<IVersion> version;
    std::unique_ptr<IPackages> packages;
};

}