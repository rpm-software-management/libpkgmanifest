// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "parserfactory.hpp"
#include "parser.hpp"

#include "impl/common/objects/repository/repositoryfactory.hpp"
#include "impl/common/objects/repository/repositoryparser.hpp"
#include "impl/common/objects/repositories/repositoriesfactory.hpp"
#include "impl/common/objects/repositories/repositoriesparser.hpp"
#include "impl/common/objects/version/versionfactory.hpp"
#include "impl/common/objects/version/versionparser.hpp"
#include "impl/common/operations/stringlistparser/stringlistparser.hpp"
#include "impl/common/tools/stringsplitter/stringsplitter.hpp"
#include "impl/common/yaml/yamlparser.hpp"
#include "impl/common/yaml/yamlnodefactory.hpp"
#include "impl/input/objects/input/inputfactory.hpp"
#include "impl/input/objects/input/inputparser.hpp"
#include "impl/input/objects/modules/modulesfactory.hpp"
#include "impl/input/objects/modules/modulesparser.hpp"
#include "impl/input/objects/options/optionsfactory.hpp"
#include "impl/input/objects/options/optionsparser.hpp"
#include "impl/input/objects/packages/packagesfactory.hpp"
#include "impl/input/objects/packages/packagesparser.hpp"
#include "impl/input/operations/prototypefileconverter/prototypefileconverter.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

std::unique_ptr<IParser> ParserFactory::create() const {
    auto node_factory = std::make_shared<YamlNodeFactory>();
    auto string_splitter = std::make_shared<StringSplitter>();

    auto repository_factory = std::make_shared<RepositoryFactory>();
    auto repository_parser = std::make_unique<RepositoryParser>(repository_factory);

    auto repositories_factory = std::make_shared<RepositoriesFactory>();
    auto repositories_parser = std::make_shared<RepositoriesParser>(std::move(repository_parser), repositories_factory);

    auto version_factory = std::make_shared<VersionFactory>();
    auto version_parser = std::make_shared<VersionParser>(version_factory, string_splitter);

    auto string_list_parser = std::make_shared<StringListParser>();

    auto packages_factory = std::make_shared<PackagesFactory>();
    auto packages_parser = std::make_shared<PackagesParser>(packages_factory, string_list_parser);

    auto modules_factory = std::make_shared<ModulesFactory>();
    auto modules_parser = std::make_shared<ModulesParser>(modules_factory, string_list_parser);

    auto options_factory = std::make_shared<OptionsFactory>();
    auto options_parser = std::make_shared<OptionsParser>(options_factory);

    auto input_factory = std::make_unique<InputFactory>(
        repositories_factory,
        version_factory,
        packages_factory,
        modules_factory,
        options_factory
    );

    auto input_parser = std::make_unique<InputParser>(
        std::move(input_factory),
        repositories_parser,
        version_parser,
        packages_parser,
        modules_parser,
        options_parser,
        string_list_parser
    );

    auto prototype_converter = std::make_unique<PrototypeFileConverter>(node_factory);

    auto yaml_parser = std::make_unique<YamlParser>();

    return std::make_unique<Parser>(
        std::move(yaml_parser),
        std::move(input_parser),
        std::move(prototype_converter)
    );
}

}