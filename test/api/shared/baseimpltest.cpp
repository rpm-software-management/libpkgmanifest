#include "api/shared/base_impl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest;

TEST(ApiBaseImplTest, ThrowsWhenObjectFactoryIsNotDefaultConstructible) {
    class Object {
    public:
        virtual ~Object() = default;
        virtual std::unique_ptr<Object> clone() const {
            return std::make_unique<Object>(*this);
        }
    };
    
    class NonDefaultConstructibleFactory {
    public:
        explicit NonDefaultConstructibleFactory(int) {}

        std::unique_ptr<Object> create() const {
            return std::make_unique<Object>();
        }
    };

    class NonDefaultConstructible : public BaseImpl<Object, NonDefaultConstructibleFactory> {};

    EXPECT_THROW(NonDefaultConstructible().get(), std::runtime_error);
}

}