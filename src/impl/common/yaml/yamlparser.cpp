// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "yamlnode.hpp"
#include "yamlparser.hpp"

#include <yaml-cpp/yaml.h>

namespace libpkgmanifest::internal::common {

YamlFileError::YamlFileError(const std::string & message)
    : std::runtime_error(message) {}

YamlParseError::YamlParseError(const std::string & message)
    : std::runtime_error(message) {}

std::unique_ptr<IYamlNode> YamlParser::from_string(const std::string & yaml) const {
    try {
        return std::make_unique<YamlNode>(YAML::Load(yaml));
    } catch(YAML::ParserException & ex) {
        throw YamlParseError(ex.msg);
    }
}

std::unique_ptr<IYamlNode> YamlParser::from_file(const std::string & path) const {
    try {
        return std::make_unique<YamlNode>(YAML::LoadFile(path));
    } catch(YAML::BadFile & ex) {
        throw YamlFileError(ex.msg);
    } catch(YAML::ParserException & ex) {
        throw YamlParseError(ex.msg);
    }
}

}
