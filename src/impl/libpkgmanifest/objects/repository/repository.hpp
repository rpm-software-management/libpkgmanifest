#pragma once

#include "irepository.hpp"

namespace libpkgmanifest::internal {

class Repository : public IRepository {
public:
    Repository();

    virtual std::unique_ptr<IRepository> clone() const override;

    virtual std::string get_id() const override;
    virtual std::string get_url() const override;

    virtual void set_id(const std::string & id) override;
    virtual void set_url(const std::string & url) override;

private:
    std::string id;
    std::string url;
};

}