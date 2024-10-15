#include "repository.hpp"

namespace libpkgmanifest::internal {

Repository::Repository()
    : id()
    , baseurl()
    , metalink()
    , mirrorlist() {}

std::unique_ptr<IRepository> Repository::clone() const {
    return std::unique_ptr<IRepository>(new Repository(*this));
}

std::string Repository::get_id() const {
    return id;
}

std::string Repository::get_baseurl() const {
    return baseurl;
}

std::string Repository::get_metalink() const {
    return metalink;
}

std::string Repository::get_mirrorlist() const {
    return mirrorlist;
}

void Repository::set_id(const std::string & id) {
    this->id = id;
}

void Repository::set_baseurl(const std::string & baseurl) {
    this->baseurl = baseurl;
}

void Repository::set_metalink(const std::string & metalink) {
    this->metalink = metalink;
}

void Repository::set_mirrorlist(const std::string & mirrorlist) {
    this->mirrorlist = mirrorlist;
}

}