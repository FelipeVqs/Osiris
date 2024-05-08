#include <cstddef>
#include <cstring>

extern "C" int _fltused{ 0x9875 };

namespace intrinsics
{

[[nodiscard]] constexpr inline int memcmp(const std::byte* lhs, const std::byte* rhs, std::size_t count) noexcept
{
    for (std::size_t i = 0; i < count; ++i) {
        if (lhs[i] != rhs[i])
            return lhs[i] < rhs[i] ? -1 : 1;
    }
    return 0;
}

constexpr inline std::byte* memcpy(std::byte* dest, const std::byte* src, std::size_t count) noexcept
{
    for (std::size_t i = 0; i < count; ++i)
        dest[i] = src[i];
    return dest;
}

constexpr inline std::byte* memset(std::byte* dest, std::byte ch, std::size_t count) noexcept
{
    for (std::size_t i = 0; i < count; ++i)
        dest[i] = ch;
    return dest;
}

[[nodiscard]] constexpr inline int strcmp(const char* s1, const char* s2) noexcept
{
    while (*s1 == *s2) {
        if (*s1 == '\0')
            return 0;
        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}

constexpr inline std::byte* memmove(std::byte* dest, const std::byte* src, std::size_t count) noexcept
{
    if (dest < src) {
        for (std::size_t i = 0; i < count; ++i)
            dest[i] = src[i];
    } else {
        for (std::size_t i = count; i > 0; --i)
            dest[i - 1] = src[i - 1];
    }
    return dest;
}

constexpr inline std::size_t strlen(const char* str) noexcept
{
    std::size_t length = 0;
    while (*str) {
        ++length;
        ++str;
    }
    return length;
}

constexpr inline const std::byte* memchr(const std::byte* ptr, std::byte ch, std::size_t count) noexcept
{
    for (std::size_t i = 0; i < count; ++i) {
        if (ptr[i] == ch)
            return &ptr[i];
    }
    return nullptr;
}

} // namespace intrinsics

constexpr void* memcpy(void* dest, const void* src, std::size_t count)
{
    return intrinsics::memcpy(static_cast<std::byte*>(dest), static_cast<const std::byte*>(src), count);
}

constexpr void* memmove(void* dest, const void* src, std::size_t count)
{
    return intrinsics::memmove(static_cast<std::byte*>(dest), static_cast<const std::byte*>(src), count);
}

constexpr int memcmp(const void* s1, const void* s2, std::size_t n)
{
    return intrinsics::memcmp(static_cast<const std::byte*>(s1), static_cast<const std::byte*>(s2), n);
}

constexpr void* memset(void* dest, int ch, std::size_t count)
{
    return intrinsics::memset(static_cast<std::byte*>(dest), static_cast<std::byte>(ch), count);
}

constexpr int strcmp(const char* s1, const char* s2)
{
    return intrinsics::strcmp(s1, s2);
}

constexpr std::size_t strlen(const char* str)
{
    return intrinsics::strlen(str);
}

constexpr const void* memchr(const void* ptr, int ch, std::size_t count)
{
    return intrinsics::memchr(static_cast<const std::byte*>(ptr), static_cast<std::byte>(ch), count);
}
