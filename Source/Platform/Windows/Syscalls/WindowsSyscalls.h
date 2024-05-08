#pragma once

#include <Windows.h>
#include <winternl.h>

#include "SyscallParams.h"
#include "WindowsSyscallIndex.h"

extern "C" std::size_t systemCall(const SyscallParams& params, ...);

struct IO_APC_ROUTINE;

struct WindowsSyscalls final {
    template <typename... Args>
    static NTSTATUS NtCreateFile(Args... args) noexcept {
        const SyscallParams params{WindowsSyscallIndex::NtCreateFile, 0};
        return static_cast<NTSTATUS>(systemCall(params, args...));
    }

    template <typename... Args>
    static NTSTATUS NtReadFile(Args... args) noexcept {
        const SyscallParams params{WindowsSyscallIndex::NtReadFile, 0};
        return static_cast<NTSTATUS>(systemCall(params, args...));
    }

    static NTSTATUS NtClose(HANDLE handle) noexcept {
        const SyscallParams params{WindowsSyscallIndex::NtClose, reinterpret_cast<std::uintptr_t>(handle)};
        return static_cast<NTSTATUS>(systemCall(params));
    }

private:
    template <typename... Args>
    static std::enable_if_t<sizeof...(Args) == 10, NTSTATUS> systemCallWrapper(const SyscallParams& params, Args... args) noexcept {
        return static_cast<NTSTATUS>(systemCall(params, std::forward<Args>(args)...));
    }

    template <typename... Args>
    static std::enable_if_t<sizeof...(Args) != 10, NTSTATUS> systemCallWrapper(const SyscallParams&) noexcept {
        static_assert(sizeof...(Args) == 1, "Invalid number of arguments");
        return 0;
    }
};
