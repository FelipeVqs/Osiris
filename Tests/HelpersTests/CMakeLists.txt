add_executable(Tests BitsTests.cpp)

target_sources(Bits PRIVATE
  Bit.cpp
)

target_sources(Tests PRIVATE
  BitsTests.cpp
)

target_link_libraries(Tests PRIVATE Bits)
