# Set the minimum version for CMake
cmake_minimum_required(VERSION 3.12)

# Set the project name and language
project(Osiris VERSION 1.0 LANGUAGES CXX ASM)

# Add the shared library target
add_library(Osiris SHARED dllmain.cpp)

# Set target properties
set_target_properties(Osiris PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  C_VISIBILITY_PRESET hidden
  POSITION_INDEPENDENT_CODE ON)

# Add include directories
target_include_directories(Osiris PRIVATE "${CMAKE_SOURCE_DIR}/Source")

# Link libraries
target_link_libraries(Osiris PRIVATE ${CMAKE_DL_LIBS})

# Add platform-specific source files
if(WIN32)
  target_sources(Osiris PRIVATE
    Platform/Windows/Syscalls/WindowsSyscall.asm
    Platform/Windows/Endpoints.asm)
endif()

if(UNIX)
  target_sources(Osiris PRIVATE
    Platform/Linux/Endpoints.s)
endif()

# Configure MSVC compiler options
if(MSVC)
  string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  target_sources(Osiris PRIVATE $<$<CONFIG:Release>:Intrinsics.cpp>)
  target_compile_options(Osiris PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:/W4 $<$<CONFIG:Release>:/sdl- /GS->>)
  target_link_options(Osiris PRIVATE
    $<$<CONFIG:Release>:/nodefaultlib /ENTRY:"DllMain">)
endif()

# Configure compiler and linker options for Clang and GNU compilers
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(NOT CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options(Osiris PRIVATE
      $<$<COMPILE_LANGUAGE:CXX>:-Wall>)
    target_link_options(Osiris PRIVATE
      LINKER:--no-undefined)
  endif()

  target_compile_options(Osiris PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-missing-braces>)
endif()

# Configure Release build options for Unix platforms
if(CMAKE_BUILD_TYPE STREQUAL "Release" AND UNIX)
  target_compile_options(Osiris PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-fno-stack-protector -fno-exceptions -fno-asynchronous-unwind-tables -fno-unwind-tables>)
  target_link_options(Osiris PRIVATE
    -nostdlib)
  target_link_libraries(Osiris PRIVATE
    c)

  add_custom_command(TARGET Osiris POST_BUILD COMMAND
    ${CMAKE_STRIP} "$<TARGET_FILE:Osiris>")
endif()
