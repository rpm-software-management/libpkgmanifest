#include "options.hpp"
#include "optionsfactory.hpp"

namespace libpkgmanifest::internal::input {

std::unique_ptr<IOptions> OptionsFactory::create() const {
    return std::make_unique<Options>();
}   

}