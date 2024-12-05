#pragma once

#include "irepository.hpp"

namespace libpkgmanifest::internal::common {

class Repository : public IRepository {
public:
    Repository();

    virtual std::unique_ptr<IRepository> clone() const override;

    virtual std::string get_id() const override;
    virtual std::string get_baseurl() const override;
    virtual std::string get_metalink() const override;
    virtual std::string get_mirrorlist() const override;

    virtual void set_id(const std::string & id) override;
    virtual void set_baseurl(const std::string & baseurl) override;
    virtual void set_metalink(const std::string & metalink) override;
    virtual void set_mirrorlist(const std::string & mirrorlist) override;

private:
    std::string id;
    std::string baseurl;
    std::string metalink;
    std::string mirrorlist;
};

}