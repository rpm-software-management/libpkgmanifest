// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <map>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

namespace libpkgmanifest::internal::common {

class IYamlNode {
public:
    virtual ~IYamlNode() = default;

    virtual bool has(const std::string & key) const = 0;
    virtual std::unique_ptr<IYamlNode> get(const std::string & key) const = 0;

    virtual std::string as_string() const = 0;
    virtual bool as_bool() const = 0;
    virtual int as_int() const = 0;
    virtual unsigned as_uint() const = 0;
    virtual uint64_t as_uint64() const = 0;
    virtual std::vector<std::unique_ptr<IYamlNode>> as_list() const = 0;
    virtual std::map<std::string, std::unique_ptr<IYamlNode>> as_map() const = 0;
};

}