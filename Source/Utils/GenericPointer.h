#pragma once

template <typename T>
concept Pointer = std::is_pointer_v<T>;

struct GenericPointer {
    template <Pointer Ptr>
    explicit(false) GenericPointer(Ptr pointer) noexcept
        : value(pointer)
    {
    }

    GenericPointer() = default;
    GenericPointer(const GenericPointer&) = delete;
    GenericPointer& operator=(const GenericPointer&) = delete;

    ~GenericPointer() = default;

    [[nodiscard]] explicit operator bool() const noexcept
    {
        return value != nullptr;
    }

    template <typename T>
    [[nodiscard]] T as() const noexcept
    {
        static_assert<Pointer<T*>, "T must be a pointer type");
        return *static_cast<T*>(value);
    }

    T* get() const noexcept
    {
        return static_cast<T*>(value);
    }

    void reset() noexcept
    {
        value = nullptr;
    }

    T* release() noexcept
    {
        T* temp = get();
        value = nullptr;
        return temp;
    }

private:
    void* value{};
};
