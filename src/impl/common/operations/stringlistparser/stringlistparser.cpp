#include "stringlistparser.hpp"

namespace libpkgmanifest::internal::common {

StringListParser::StringListParser() {}

std::vector<std::string> StringListParser::parse(const IYamlNode & node) const {
    std::vector<std::string> items;
    for (auto & item_node : node.as_list()) {
        items.push_back(item_node->as_string());
    }
    return items;
}

}