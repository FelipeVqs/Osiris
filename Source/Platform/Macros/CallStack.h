#pragma once

#include <cstdint>
#include <type_traits>

#include "IsPlatform.h"
#include <Utils/ReturnAddress.h>

#if IS_WIN64()

#include <intrin.h>

#define HAS_RETURN_ADDRESS _has_return_address
#define HAS_FRAME_ADDRESS __has_builtin(__builtin_frame_address)

#elif IS_LINUX()

#define HAS_RETURN_ADDRESS __has_builtin(__builtin_return_address)
#define HAS_FRAME_ADDRESS 1

#else

#define HAS_RETURN_ADDRESS 0
#define HAS_FRAME_ADDRESS 0

#endif

#if HAS_RETURN_ADDRESS

#define RETURN_ADDRESS() ReturnAddress<std::integral_constant<bool, HAS_RETURN_ADDRESS>>{_ReturnAddress()}

#else

#define RETURN_ADDRESS()

#endif

#if HAS_FRAME_ADDRESS

#define FRAME_ADDRESS() std::uintptr_t(const_cast<std::uintptr_t*>(__builtin_frame_address(0)))

#define FRAME_ADDRESS_CONSTEXPR() std::uintptr_t(__builtin_frame_address(0))

#else

#define FRAME_ADDRESS()
#define FRAME_ADDRESS_CONSTEXPR()

#endif

namespace Utils {

template <typename T = std::true_type>
class ReturnAddress {
public:
    constexpr ReturnAddress(void* address) noexcept : address_(address) {}

    void* get() const noexcept { return address_; }

private:
    void* address_;
};

}  // namespace Utils
