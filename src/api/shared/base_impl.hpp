#pragma once

#include <memory>
#include <type_traits>

namespace libpkgmanifest {

template <typename Object, typename ObjectFactory>
class BaseImpl {
public:
    BaseImpl() = default;

    BaseImpl(const BaseImpl & other) {
        copy_object(other);
    }

    BaseImpl & operator=(const BaseImpl & other) {
        if (this != &other) {
            copy_object(other);
        }
        return *this;
    }

    virtual Object * get() {
        ensure_object_exists();
        return object;
    }

    virtual std::unique_ptr<Object> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_object);
    }

    virtual void init(Object * obj) {
        this->object = obj;
    }

protected:
    virtual void copy_object(const BaseImpl & other) {
        if (other.object) {
            factory_object = other.object->clone();
            init(factory_object.get());
        }
    }

    virtual void ensure_object_exists() {
        if constexpr (std::is_default_constructible<ObjectFactory>::value) {
            if (!object) {
                factory_object = ObjectFactory().create();
                init(factory_object.get());
            }
        } else {
            throw std::runtime_error("Object factory is not default constructible.");
        }
    }

    Object * object = nullptr;
    std::unique_ptr<Object> factory_object;
};

}