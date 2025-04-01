#include "api/shared/base_impl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest;

class Object {
public:
    virtual ~Object() = default;
    virtual std::unique_ptr<Object> clone() const {
        return std::make_unique<Object>(*this);
    }
};

class DefaultConstructibleFactory {
public:
    DefaultConstructibleFactory() = default;

    std::unique_ptr<Object> create() const {
        return std::make_unique<Object>();
    }
};

class NonDefaultConstructibleFactory {
public:
    explicit NonDefaultConstructibleFactory(int) {}

    std::unique_ptr<Object> create() const {
        return std::make_unique<Object>();
    }
};

class DefaultConstructible : public BaseImpl<Object, DefaultConstructibleFactory> {};
class NonDefaultConstructible : public BaseImpl<Object, NonDefaultConstructibleFactory> {};

TEST(ApiBaseImplTest, ThrowsWhenObjectFactoryIsNotDefaultConstructible) {
    EXPECT_THROW(NonDefaultConstructible().get(), std::runtime_error);
}

TEST(ApiBaseImplTest, ThrowsWhenTryToTakeOutObjectWithoutOwnership) {
    Object object;
    DefaultConstructible wrapper;
    wrapper.init(&object);
    EXPECT_THROW(wrapper.get_owned_object(), std::runtime_error);
}

TEST(ApiBaseImplTest, InitializeAlreadyOwnedObjectDoesNotThrow) {
    Object object;
    DefaultConstructible wrapper;
    wrapper.get();
    wrapper.init(&object);
    wrapper.get();
}

}