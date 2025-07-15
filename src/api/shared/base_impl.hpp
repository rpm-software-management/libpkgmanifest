// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <memory>
#include <type_traits>

namespace libpkgmanifest {

/// @brief Common pimpl base for API classes, providing shared logic
///        for connecting API classes to their implementations.
///
/// @tparam ObjectInterface The interface class of the implementation.
/// @tparam ObjectFactory The factory class that creates the implementation.
template <typename ObjectInterface, typename ObjectFactory>
class BaseImpl {
public:
    BaseImpl() = default;
    virtual ~BaseImpl() = default;

    BaseImpl(const BaseImpl & other) {
        copy_object(other);
    }

    BaseImpl & operator=(const BaseImpl & other) {
        if (this != &other) {
            copy_object(other);
        }
        return *this;
    }

    /// @brief Accesses the underlying object implementation.
    ///
    /// @return A pointer to the implementation.
    virtual ObjectInterface * get() {
        ensure_object_exists();
        return object;
    }

    /// @brief Assign the ownership of the implementation to this instance.
    ///
    /// @param object A unique pointer to the implementation.
    virtual void set(std::unique_ptr<ObjectInterface> object) {
        owned_object = std::move(object);
        init(owned_object.get());
    }

    /// @brief Transfers ownership of the underlying implementation.
    ///
    /// @note Used when moving the object to its parent, which becomes
    ///       the new owner (e.g., in compound objects like Manifest, Package).
    ///
    /// @warning The object will be reset after calling this method
    ///          and must be reinitialized before accessing its data.
    ///
    /// @return A unique pointer to the implementation.
    /// @throw std::runtime_error If the implementation is not owned.
    virtual std::unique_ptr<ObjectInterface> get_owned_object() {
        ensure_object_exists();

        if (!owned_object) {
            throw std::runtime_error("Tried to take out the object without the ownership.");
        }

        object = nullptr;
        return std::move(owned_object);
    }

    /// @brief Initializes the object with a given implementation.
    ///
    /// @note This is a one way to initialize an API object's pimpl part
    ///       by directly referencing an existing implementation.
    ///
    /// @note Typically used by a parser that has already created
    ///       implementation objects and composed a Manifest object,
    ///       which then assumes ownership. In this case, only a reference
    ///       to the object is stored.
    ///
    /// @param obj A pointer to the implementation.
    virtual void init(ObjectInterface * object) {
        this->object = object;
        if (owned_object && owned_object.get() != object) {
            owned_object = nullptr;
        }
    }

protected:
    /// @brief Copies the implementation from another instance.
    ///
    /// @note When copying, the implementation is cloned, making
    ///       this instance its owner.
    ///
    /// @param other The source instance.
    virtual void copy_object(const BaseImpl & other) {
        if (other.object) {
            owned_object = other.object->clone();
            init(owned_object.get());
        }
    }

    /// @brief Ensures the object is initialized.
    ///
    /// @note  This provides an alternative way to initialize an API object's pimpl part,
    ///        in addition to the 'init' method.
    ///
    /// @note  If the object has not been created or initialized yet,
    ///        this method initializes it using the connected factory. In such cases,
    ///        the object is created upon the first attempt to access its data,
    ///        making this instance the owner of the implementation.
    ///
    /// @throw std::runtime_error If the object factory is not default-constructible.
    ///                           This should not occur and must be handled in a subclass
    ///                           by overriding this method.
    virtual void ensure_object_exists() {
        if (object) {
            return;
        }

        if constexpr (std::is_default_constructible<ObjectFactory>::value) {
            owned_object = ObjectFactory().create();
            init(owned_object.get());
        } else {
            throw std::runtime_error("Object factory is not default constructible.");
        }
    }

    ObjectInterface * object = nullptr;
    std::unique_ptr<ObjectInterface> owned_object;
};

}