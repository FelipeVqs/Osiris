#pragma once

#if IS_WIN64()
#include "Windows/WindowsDynamicLibrary.h"
#elif IS_LINUX()
#include "Linux/LinuxDynamicLibrary.h"
#endif

#if IS_WIN64() || IS_LINUX()
using DynamicLibrary = /* the type defined in the included header */;
#endif
