#pragma once

#include <type_traits>
#include <utility>

template <typename R, typename... Args>
struct GenericFunctionPointer {
    template <typename F>
    explicit(std::is_convertible_v<F, R(*)(Args...)>)
    GenericFunctionPointer(F function) noexcept
        : value_{reinterpret_cast<R(*)(Args...)>(function)}
    {
    }

    template <typename F>
    explicit(std::is_convertible_v<F, R(*)(Args...)>)
    operator F() const noexcept
    {
        return reinterpret_cast<F>(value_);
    }

    R operator()(Args... args) const noexcept
    {
        return reinterpret_cast<R(*)(Args...)>(value_)(std::forward<Args>(args)...);
    }

private:
    R (*value_)(Args...);
};

template <typename R, typename... Args>
GenericFunctionPointer<R, Args...> make_generic_function_pointer(R(*function)(Args...))
{
    return function;
}
