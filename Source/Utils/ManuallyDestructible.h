#pragma once

#include <cassert>
#include <cstddef>
#include <new>
#include <utility>

template <typename T>
struct ManuallyDestructible {
    static_assert(std::is_object<T>::value, "T must be an object type");

    ManuallyDestructible() = default;

    ManuallyDestructible(const ManuallyDestructible&) = delete;
    ManuallyDestructible(ManuallyDestructible&&) = delete;

    ManuallyDestructible& operator=(const ManuallyDestructible&) = delete;
    ManuallyDestructible& operator=(ManuallyDestructible&&) = delete;

    template <typename... Args>
    ManuallyDestructible(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args...>::value)
        : object_(new (&storage_) T(std::forward<Args>(args)...))
    {
    }

    ManuallyDestructible(T* ptr) noexcept
        : object_(ptr)
    {
    }

    ManuallyDestructible(ManuallyDestructible&& other) noexcept
        : ManuallyDestructible()
    {
        swap(other);
    }

    ~ManuallyDestructible() noexcept
    {
        reset();
    }

    template <typename U, typename... Args>
    void emplace(Args&&... args) noexcept(std::is_nothrow_constructible<U, Args...>::value)
    {
        reset();
        new (&storage_) U(std::forward<Args>(args)...);
        object_ = reinterpret_cast<T*>(&storage_);
    }

    template <typename U>
    void move_from(ManuallyDestructible<U>&& other) noexcept
    {
        assert(this != std::addressof(other));
        reset();
        new (&storage_) T(std::move(*other));
        object_ = reinterpret_cast<T*>(&storage_);
    }

    T* operator->() noexcept
    {
        assert(isInitialized());
        return object_;
    }

    T& operator*() noexcept
    {
        assert(isInitialized());
        return *object_;
    }

    const T* operator->() const noexcept
    {
        assert(isInitialized());
        return object_;

