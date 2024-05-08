#pragma once

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace utils
{

template <typename T, typename Tuple, std::size_t I = 0>
[[nodiscard]] consteval std::size_t typeIndex() noexcept
requires (std::is_same_v<std::remove_cv_t<std::remove_reference_t<Tuple>>, std::tuple<>> ||
         (std::tuple_size_v<std::remove_cv_t<std::remove_reference_t<Tuple>>> >= I))
{
    static_assert(!std::is_array_v<T>, "T cannot be an array type");
    static_assert(!std::is_function_v<T>, "T cannot be a function type");
    static_assert(!std::is_pointer_v<T> && !std::is_pointer_v<std::remove_pointer_t<T>>,
                  "T cannot be a pointer to a function");

    static_assert(I < std::tuple_size_v<Tuple>, "T does not exist in Tuple");

    if constexpr (std::is_same_v<T, std::tuple_element_t<I, Tuple>>)
        return I;
    else
        return typeIndex<T, Tuple, I + 1>();
}

}

