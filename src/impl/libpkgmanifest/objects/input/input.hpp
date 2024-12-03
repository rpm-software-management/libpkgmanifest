#pragma once

#include "iinput.hpp"

namespace libpkgmanifest::internal {

class Input : public IInput {
public:
    Input();
    Input(const Input & other);

    virtual std::unique_ptr<IInput> clone() const override;

    virtual std::string get_document() const override;
    virtual const IVersion & get_version() const override;
    virtual IVersion & get_version() override;
    virtual const IRepositories & get_repositories() const override;
    virtual IRepositories & get_repositories() override;
    virtual const std::map<std::string, std::vector<std::string>> & get_packages() const override;
    virtual std::map<std::string, std::vector<std::string>> & get_packages() override;
    virtual const std::map<std::string, std::vector<std::string>> & get_modules() const override;
    virtual std::map<std::string, std::vector<std::string>> & get_modules() override;
    virtual const std::vector<std::string> & get_archs() const override;
    virtual std::vector<std::string> & get_archs() override;
    virtual bool get_allow_erasing() const override;

    virtual void set_document(const std::string & document) override;
    virtual void set_version(std::unique_ptr<IVersion> version) override;
    virtual void set_repositories(std::unique_ptr<IRepositories> repositories) override;
    virtual void set_allow_erasing(bool allow_erasing) override;

private:
    std::string document;
    std::unique_ptr<IVersion> version;
    std::unique_ptr<IRepositories> repositories;
    std::map<std::string, std::vector<std::string>> packages;
    std::map<std::string, std::vector<std::string>> modules;
    std::vector<std::string> archs;
    bool allow_erasing;
};

}