#include "yamlnode.hpp"
#include "yamlparser.hpp"

namespace liblockfile {

YamlFileError::YamlFileError(const std::string & message)
    : std::runtime_error(message) {}

YamlParseError::YamlParseError(const std::string & message)
    : std::runtime_error(message) {}

std::unique_ptr<IYamlNode> YamlParser::from_string(const std::string & yaml) const {
    try {
        return std::unique_ptr<YamlNode>(new YamlNode(YAML::Load(yaml)));
    } catch(YAML::ParserException & ex) {
        throw YamlParseError(ex.msg);
    }
}

std::unique_ptr<IYamlNode> YamlParser::from_file(const std::string & path) const {
    try {
        return std::unique_ptr<YamlNode>(new YamlNode(YAML::LoadFile(path)));
    } catch(YAML::BadFile & ex) {
        throw YamlFileError(ex.msg);
    }
}

}
