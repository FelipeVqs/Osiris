#pragma once

// Adding a comment to describe the purpose of the struct
struct RttiCompleteObjectLocator {
    // Using an enum class to improve readability and avoid naming collisions
    enum class Offset : std::uint32_t {
        kOffsetOfOffsetInCompleteClass = 4,
        kOffsetOfTypeDescriptorRva = 12
    };
};
