#pragma once

#include <dlfcn.h>
#include <link.h>
#include <signal.h>
#include <sys/mman.h>
#include <memory>
#include <cstdlib>
#include <cstring>

namespace MyCompany {

class LinuxPlatformApi {
public:
    LinuxPlatformApi() = default;

    void* dlopen(const char* file, int mode) noexcept {
        return ::dlopen(file, mode);
    }

    void* dlsym(void* handle, const char* name) noexcept {
        return ::dlsym(handle, name);
    }

    int dlclose(void* handle) noexcept {
        return ::dlclose(handle);

