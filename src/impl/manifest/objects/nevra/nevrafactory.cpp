#include "nevra.hpp"
#include "nevrafactory.hpp"

namespace libpkgmanifest::internal::manifest {

std::unique_ptr<INevra> NevraFactory::create() const {
    return std::unique_ptr<INevra>(new Nevra());
}   

}