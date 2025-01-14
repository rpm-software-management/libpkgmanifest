#include "optionsparser.hpp"

namespace libpkgmanifest::internal::input {

OptionsParser::OptionsParser(std::shared_ptr<IOptionsFactory> options_factory)
    : options_factory(std::move(options_factory)) {}

std::unique_ptr<IOptions> OptionsParser::parse(const IYamlNode & node) const {
    auto options = options_factory->create();

    if (node.has("allow_erasing")) {
        options->set_allow_erasing(node.get("allow_erasing")->as_bool());
    }

    return options;
}

}