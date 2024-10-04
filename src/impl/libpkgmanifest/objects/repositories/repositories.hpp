#pragma once

#include "irepositories.hpp"

namespace libpkgmanifest::internal {

class Repositories : public IRepositories {
public:
    Repositories();
    Repositories(const Repositories & other);

    virtual std::unique_ptr<IRepositories> clone() const override;

    virtual std::map<std::string, std::unique_ptr<IRepository>> & get() override;
    virtual const std::map<std::string, std::unique_ptr<IRepository>> & get() const override;
    virtual void add(std::unique_ptr<IRepository> package) override;

private:
    std::map<std::string, std::unique_ptr<IRepository>> repositories;
};

}