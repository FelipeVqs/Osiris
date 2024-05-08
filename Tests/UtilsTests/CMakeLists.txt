# Use variable to store the test source files
set(TEST_SOURCES
  FlagsBuilderTests.cpp
  PatternFinderTests.cpp
  RefCountedHookTests.cpp
  ReturnAddressTests.cpp
  SpanSliceTests.cpp
  StringBuilderTests.cpp
)

# Use target_sources with the APPEND option to add the test sources to the Tests target
target_sources(Tests PRIVATE
  ${TEST_SOURCES}
)
