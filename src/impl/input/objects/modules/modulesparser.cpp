#include "modulesparser.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

ModulesParser::ModulesParser(
    std::shared_ptr<IModulesFactory> modules_factory,
    std::shared_ptr<IStringListParser> string_list_parser)
    : modules_factory(modules_factory)
    , string_list_parser(string_list_parser) {}

std::unique_ptr<IModules> ModulesParser::parse(const IYamlNode & node) const {
    auto modules = modules_factory->create();

    if (node.has("enable")) {
        auto source_enables = string_list_parser->parse(*node.get("enable"));
        modules->get_enables().assign(std::make_move_iterator(source_enables.begin()),
                                      std::make_move_iterator(source_enables.end()));
    }

    if (node.has("disable")) {
        auto source_disables = string_list_parser->parse(*node.get("disable"));
        modules->get_disables().assign(std::make_move_iterator(source_disables.begin()),
                                       std::make_move_iterator(source_disables.end()));
    }

    return modules;
}

}